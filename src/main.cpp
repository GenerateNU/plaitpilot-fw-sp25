#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include "potentiometer.h"
#include "VL6180X.h"
#include "BasicStepperDriver.h"


enum State
{
  GATHER_INPUTS = 0, // gather inputs for the size and quantity of hair, and display
  DRIVE_MOTOR = 1,   // drive motor for one, specific to the size gathered
  HOOK_MOTOR = 2,    // hook the motor for one bunch of hair (/\ these two happen in loop of 5)
  // this also updates the display to show the number of bunches left
  CONTINUE_JOB = 3, // continue the job, if there are more bunches to do, wait for button to be pressed
  // this is so the potentiometers don't override the previous values of like whatever - 5
};

#define RPM 120
#define MICROSTEPS 1
#define MOTOR_STEPS 200
#define DIR1 12
#define STEP1 27
#define DIR2 13
#define STEP2 14

BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);
State curState = GATHER_INPUTS;
PotValues values;
int currentBunches = 5;
int totalBunches = 0;
int currentSize = 0;
int buttonTimer = 0;
const int buttonPin = 33;
const int buttonLED = 32;


void setup()
{
  Serial.begin(115200);
  lcd_init();
  update_pot_display(readPotentiometerValues());
  stepper1.begin(RPM, MICROSTEPS);
  stepper2.begin(RPM, MICROSTEPS);
  pinMode(buttonPin, INPUT);
  pinMode(buttonLED, OUTPUT);

}

void loop()
{
  switch (curState)
  {
  case GATHER_INPUTS:
  {
    delay(500);
    while (true)
    {
      buttonTimer += digitalRead(33); 
      Serial.println(digitalRead(33));
      if(buttonTimer >= 500) {
        //break;
      }

      if (potentiometerUpdated())
      {
        PotValues values = readPotentiometerValues();
        update_pot_display(values);
      }
    }
    buttonTimer = 0;
    Serial.println("Passed");
    button_pressed();
    
    digitalWrite(buttonLED, HIGH);
    delay(1000);
    digitalWrite(buttonLED, LOW);

    currentBunches = 5;
    totalBunches = values.quantity;
    currentSize = values.size;
    curState = DRIVE_MOTOR;
    break;
  }
  case DRIVE_MOTOR:
  {
    Serial.println("DRIVING");
    if (currentBunches <= 0)
    {
      curState = CONTINUE_JOB;
      break;
    }
    else {
      //60 is temp, testing to find value, multiple of size
      stepper1.rotate(60);
    }

    /*
    gather data from the potentiometer sensor ruler thing
    drive the motor until the sensor reads the correct value (due to the size of the bunch)
    */
    curState = HOOK_MOTOR;
    break;
  }
  case HOOK_MOTOR:
  {
    Serial.println("HOOKING");
    /*
    drive the hook to pick up one bunch of hair (well figure this out through testing)
    update the display
    */
    currentBunches--;

    //60 is temporary pre testing, though its a constant
    stepper2.rotate(60);
    if(currentBunches > 0) {
      curState = DRIVE_MOTOR;
    }
    else {
      curState = CONTINUE_JOB;
    }
    break;
  }
  case CONTINUE_JOB:
  {
    Serial.println("DONE");
    if (totalBunches == 0)
    {
      curState = GATHER_INPUTS;
      break;
    }
    currentBunches = 5;
    totalBunches -= 1; // only -1 because this is in bunches of 5
    /*
      wait for the button to be pressed
    */
    break;
  }
}
}