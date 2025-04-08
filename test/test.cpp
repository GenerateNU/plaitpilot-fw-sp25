#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include "potentiometer.h"
#include "VL6180X.h"
#include <BasicStepperDriver.h>

#define MOTOR_STEPS 200
#define RPM 30
#define MICROSTEPS 1
#define DIR1 32
#define STEP1 33
#define DIR2 22
#define STEP2 23

BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);

void setup() {
    Serial.begin(115200);
    lcd_init();
    update_pot_display(readPotentiometerValues());
    Wire.begin(19, 18);
    pinMode(buttonPin, INPUT_PULLUP);

    // tof initilization
    Sensor.init();
    Sensor.configureDefault();
    Sensor.setTimeout(500);

    stepper1.begin(RPM, MICROSTEPS);
    stepper2.begin(RPM, MICROSTEPS);
}

void loop() {
    do {
        int tofVal = Sensor.readRangeSingleMillimeters();
        stepper1.rotate(1);
        // stepper2.rotate(360);
        // Pause before repeating
        // delay(2000);
    } while (tofVal >= 50)
}