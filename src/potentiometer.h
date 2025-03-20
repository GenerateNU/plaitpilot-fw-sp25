#include <Arduino.h>

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

typedef struct {
    uint16_t size;
    uint16_t quantity;
} PotValues;

PotValues readPotentiometerValues();
bool potentiometerUpdated();

#endif // POTENTIOMETER_H