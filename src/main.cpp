#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Wire.h>
#include "potentiometer.h"
#include "VL6180X.h"
#include "BasicStepperDriver.h"
#include "VL6180X.h"
#include <Adafruit_I2CDevice.h>


// enum State
// {
//   GATHER_INPUTS = 0, // gather inputs for the size and quantity of hair, and display
//   DRIVE_MOTOR = 1,   // drive motor for one, specific to the size gathered
//   HOOK_MOTOR = 2,    // hook the motor for one bunch of hair (/\ these two happen in loop of 5)
//   // this also updates the display to show the number of bunches left
//   CONTINUE_JOB = 3, // continue the job, if there are more bunches to do, wait for button to be pressed
//   // this is so the potentiometers don't override the previous values of like whatever - 5
//   ADVANCE_MOTOR = 4, // advance the motor to the next position
// };

// #define RPM 120
// #define MICROSTEPS 1
// #define MOTOR_STEPS 200
// // #define DIR1 12
// // #define STEP1 27
// #define DIR1 27 //PCB
// #define STEP1 26 //PCB
// #define DIR2 13
// #define STEP2 14


// BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
// BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);
// State curState = GATHER_INPUTS;
// PotValues values;
// int currentBunches = 5;
// int totalBunches = 0;
// int currentSize = 0;
// int buttonTimer = 0;
// const int buttonPin = 33;
// const int buttonLED = 32;
// int tofVal;
// VL6180X Sensor;

// void setup()
// {
//   Serial.begin(115200);
//   lcd_init();
//   update_pot_display(readPotentiometerValues());
//   pinMode(buttonPin, INPUT);
//   pinMode(buttonLED, OUTPUT);

//   // tof initilization
//   Wire.begin();
//   Sensor.init();
//   Sensor.configureDefault();
//   Sensor.setTimeout(500);
  
//   //Motor setup
//   pinMode(12, OUTPUT);
//   digitalWrite(12, HIGH);
//   stepper1.begin(RPM, MICROSTEPS);
//   stepper2.begin(RPM, MICROSTEPS);


// }

// void loop()
// {
//   while(true) {
//     //Serial.println(Sensor.readRangeSingleMillimeters());
//     delay(1000);
//     stepper1.rotate(360);
//     // while(Sensor.readRangeSingleMillimeters() > 100) {
//     //   stepper1.rotate(1);
//     // } 
//     //   stepper1.rotate(720);
//     //   delay(3000);
//   }
//   switch (curState)
//   {
//   case GATHER_INPUTS:
//   {
//     delay(500);
//     while (true)
//     {
//       if (digitalRead(33))
//       {
//         buttonTimer += digitalRead(33);
//         if (buttonTimer >= 500)
//         {
//           break;
//         }
//       }
//       else
//       {
//         buttonTimer = 0;
//       }

//       if (potentiometerUpdated())
//       {
//         PotValues values = readPotentiometerValues();
//         update_pot_display(values);
//       }
//     }
//     buttonTimer = 0;
//     Serial.println("Passed");
//     button_pressed();

//     digitalWrite(buttonLED, HIGH);
//     delay(1000);
//     digitalWrite(buttonLED, LOW);

//     currentBunches = 5;
//     totalBunches = values.quantity;
//     currentSize = values.size;
//     curState = ADVANCE_MOTOR;
//     break;
//   }
//   case ADVANCE_MOTOR:
//   {
//     Serial.println("ADVANCING");
//     /*
//     drive the motor to the next position
//     */
//     tofVal = Sensor.readRangeSingleMillimeters();
//     if (tofVal < 100) {
//       curState = DRIVE_MOTOR;
//       break;
//     }
//     stepper1.rotate(60);
//     delay(1500);
//     break;
//   }
//   case DRIVE_MOTOR:
//   {
//     Serial.println("DRIVING");
//     if (currentBunches <= 0)
//     {
//       curState = CONTINUE_JOB;
//       break;
//     }
//     else
//     {
//       // 60 is temp, testing to find value, multiple of size
//       stepper1.rotate(60);
//       delay(3000);
//     }

//     /*
//     gather data from the potentiometer sensor ruler thing
//     drive the motor until the sensor reads the correct value (due to the size of the bunch)
//     */
//     curState = HOOK_MOTOR;
//     break;
//   }
//   case HOOK_MOTOR:
//   {
//     Serial.println("HOOKING");  
//     /*
//     drive the hook to pick up one bunch of hair (well figure this out through testing)
//     update the display
//     */
//     currentBunches--;

//     // 60 is temporary pre testing, though its a constant
//     stepper2.rotate(60);
//     delay(3000);
//     if (currentBunches > 0)
//     {
//       curState = DRIVE_MOTOR;
//     }
//     else
//     {
//       curState = CONTINUE_JOB;
//     }
//     break;
//   }
//   case CONTINUE_JOB:
//   {
//     Serial.println("DONE");
//     if (totalBunches == 0)
//     {
//       curState = GATHER_INPUTS;
//       break;
//     }
//     currentBunches = 5;
//     totalBunches -= 1; // only -1 because this is in bunches of 5
    
//     while (true)
//     {
//       if (digitalRead(33))
//       {
//         buttonTimer += digitalRead(33);
//         if (buttonTimer >= 500)
//         {
//           curState = DRIVE_MOTOR;
//           digitalWrite(buttonLED, HIGH);
//           delay(1000);
//           digitalWrite(buttonLED, LOW);
//           break;
//         }
//       }
//       else
//       {
//         buttonTimer = 0;
//       }
//       break;
//     }
//   }
//   }
// }










// #define SDA_PIN 17
// #define SCL_PIN 16


// #include <VL6180X.h>
// #include <Wire.h>
// #include <Adafruit_I2CDevice.h>
// #include <SPI.h>
// #include <Adafruit_ADS1X15.h>
// #include <Adafruit_MCP23X17.h>


// VL6180X Sensor;
// Adafruit_ADS1015 adc;

// void setup()
// {
//     Serial.begin(115200);
//     Wire.begin(SDA_PIN, SCL_PIN);

//     Sensor.init();
//     Sensor.configureDefault();
//     Sensor.setTimeout(500);

//     pinMode(33, INPUT);

//     adc.begin(0x49);
// }

// void loop()
// {
//     // Serial.print("TOF: ");
//     // Serial.print(Sensor.readRangeSingleMillimeters());
//     // Serial.print(", ");
//     // delay(100);
//     // Serial.print("POT1: ");
//     // Serial.print(adc.readADC_SingleEnded(1));                                                                                             
//     // Serial.print(", ");
//     // Serial.print("POT2: ");
//     // Serial.print(adc.readADC_SingleEnded(2));
//     Serial.println(digitalRead(33));
    
//     // if (Sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
//     // Serial.println();
// }

#include <Arduino.h>
#include <BasicStepperDriver.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 200

// Since microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 32

// Motor 1 pins
#define DIR1 27
#define STEP1 26

#define DIR2 2
#define STEP2 15

// Initialize stepper motor objects
BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);

void setup() {
    stepper1.begin(RPM, MICROSTEPS);
    stepper2.begin(RPM, MICROSTEPS);
    pinMode(12, OUTPUT);
    pinMode(0, OUTPUT);
    digitalWrite(12, HIGH);
    digitalWrite(0, HIGH);
    
    // If using enable/disable on ENABLE pin (active LOW) instead of SLEEP, uncomment next lines

}

void loop() {
    // Move both motors one full revolution
    // digitalWrite(DIR1, LOW);
    // digitalWrite(DIR2, LOW);
    stepper1.rotate(360);
    stepper2.rotate(360);
    delay(1000);
    // digitalWrite(DIR1, HIGH);
    // digitalWrite(DIR2, HIGH);
    stepper1.rotate(-360);
    stepper2.rotate(360);
    delay(1000);

    // delay(1000);
}
