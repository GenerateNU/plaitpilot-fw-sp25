#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include "potentiometer.h"
#include "VL6180X.h"

enum State {
  GATHER_INPUTS = 0, //gather inputs for the size and quantity of hair, and display
  DRIVE_MOTOR = 1, //drive motor for one, specific to the size gathered
  HOOK_MOTOR = 2, //hook the motor for one bunch of hair (/\ these two happen in loop of 5) 
  // this also updates the display to show the number of bunches left
  CONTINUE_JOB = 3, //continue the job, if there are more bunches to do, wait for button to be pressed
  // this is so the potentiometers don't override the previous values of like whatever - 5
};

State curState = GATHER_INPUTS;

PotValues values;
int currentBunches = 5;
int totalBunches = 0;
int currentSize = 0;

// Arcade button connected to GPIO 15
const int buttonPin = 15;  
int buttonState = HIGH; 

VL6180X Sensor;

void setup()
{
  Serial.begin(115200);
  lcd_init();
  update_pot_display(readPotentiometerValues());
  Wire.begin(19, 18);
  pinMode(buttonPin, INPUT_PULLUP);

  // tof initilization
  Sensor.init();
  Sensor.configureDefault();
  Sensor.setTimeout(500);
}

void loop()
{
  switch (curState)
  {
  case GATHER_INPUTS:
    /*
    while the button is not pressed, read the current potentiometer data
    update the variable to be whatever the potentiometer data is
    within the bounds of our sizes 0-10 or whatever (in bunches of 5) (so value of 3 would be 15 bunches)
    update the display to show the current values of the potentiometers
    
    when the button is pressed
    */
    values = readPotentiometerValues();
    if (buttonPressed()) {
      currentBunches = 5;
      totalBunches = values.quantity;
      currentSize = values.size;
      curState = DRIVE_MOTOR;
    } else {
      update_pot_display(values);
    }
    break;
  case DRIVE_MOTOR:
    if (currentBunches == 0)
    {
      curState = CONTINUE_JOB;
      break;
    }

    int tofVal = Sensor.readRangeSingleMillimeters();
    /*
    gather data from the potentiometer sensor ruler thing
    drive the motor until the sensor reads the correct value (due to the size of the bunch)
    */
    curState = HOOK_MOTOR;
    break;
  case HOOK_MOTOR:
    /*
    drive the hook to pick up one bunch of hair (well figure this out through testing)
    update the display
    */
    currentBunches--;
    break;
  case CONTINUE_JOB:
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


int readPotentiometerValues()
{
  int size = analogRead(34);
  int quantity = analogRead(35);
  return PotValues{size, quantity};
}

bool buttonPressed();
bool buttonPressed() {
  buttonState = digitalRead(buttonPin);
  delay(50);
  return buttonState == LOW;
}