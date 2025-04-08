#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include "potentiometer.h"
#include "VL6180X.h"

enum State
{
  GATHER_INPUTS = 0, // gather inputs for the size and quantity of hair, and display
  DRIVE_MOTOR = 1,   // drive motor for one, specific to the size gathered
  HOOK_MOTOR = 2,    // hook the motor for one bunch of hair (/\ these two happen in loop of 5)
  // this also updates the display to show the number of bunches left
  CONTINUE_JOB = 3, // continue the job, if there are more bunches to do, wait for button to be pressed
  // this is so the potentiometers don't override the previous values of like whatever - 5
};

State curState = GATHER_INPUTS;

PotValues values;
int currentBunches = 5;
int totalBunches = 0;
int currentSize = 0;
const int buttonPin = 33;
const int buttonLight = 32;
bool buttonState = false;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int reading = LOW;

void setup()
{
  Serial.begin(115200);
  lcd_init();
  update_pot_display(readPotentiometerValues());

  pinMode(buttonLight, OUTPUT); //BUTTON LIGHT PIN
  pinMode(buttonPin, INPUT); 
}

PotValues values;

int currentBunches = 5;
int totalBunches = 0;
int currentSize = 0;

void loop()
{
  switch (curState)
    {
    case GATHER_INPUTS:
    {
      /*
      while the button is not pressed, read the current potentiometer data
      update the variable to be whatever the potentiometer data is
      within the bounds of our sizes 0-10 or whatever (in bunches of 5) (so value of 3 would be 15 bunches)
      update the display to show the current values of the potentiometers

      when the button is pressed
      */
      clear_button_label();
      delay(500);
      while (!digitalRead(buttonPin))
      {
        Serial.println(digitalRead(buttonPin));
        if (potentiometerUpdated())
        {
          PotValues values = readPotentiometerValues();
          update_pot_display(values);
        }
        //reading = digitalRead(buttonPin);
      }
      digitalWrite(buttonLight, HIGH);
      button_pressed();
      delay(1000);
      digitalWrite(buttonLight, LOW);
      currentBunches = 5;
      curState = DRIVE_MOTOR;
      totalBunches = values.quantity;
      currentSize = values.size;
      break;
    }
    case DRIVE_MOTOR:
    {
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
    }
    case HOOK_MOTOR:
    {
      /*
      drive the hook to pick up one bunch of hair (well figure this out through testing)
      update the display
      */
      currentBunches--;
      break;
    }
    case CONTINUE_JOB:
    {
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

  /*
  old stuff idk what it is

  lv_timer_handler();
  delay(10);
  if (potentiometerUpdated())
  {
    PotValues values = readPotentiometerValues();
    //Serial.println(values.quantity);
    update_pot_display(values);
  }
  delay(100);
  // update_pot_display(readPotentiometerValues());
  */
}
}