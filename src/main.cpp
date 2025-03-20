#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include "potentiometer.h"

void setup()
{
  Serial.begin(115200);
  lcd_init();
  update_pot_display(readPotentiometerValues());
}

void loop()
{
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
}