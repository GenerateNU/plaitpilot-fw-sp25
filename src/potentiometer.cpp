#include <Arduino.h>
#include "potentiometer.h"

#define SZ_POT_PIN 34
#define QTY_POT_PIN 35
#define POT_THRESHOLD 10

static PotValues lastValues = {0, 0};


static uint16_t lastQuantity = 0; 

PotValues readPotentiometerValues() {
    PotValues values;

    uint16_t rawQuantity = analogRead(QTY_POT_PIN);
    uint16_t quantityMapped = map(rawQuantity, 0, 4000, 0, 50);
    uint16_t roundedQuantity = min(50, (quantityMapped / 5) * 5);

    if (abs((int)roundedQuantity - (int)lastQuantity) != 0) {
        lastQuantity = roundedQuantity; 
    }

    values.quantity = lastQuantity;
    values.size = map(analogRead(SZ_POT_PIN), 0, 3000, 0, 6);

    return values;
}


bool potentiometerUpdated() {
    PotValues current = readPotentiometerValues();

    if (current.size - lastValues.size != 0 ||
        current.quantity - lastValues.quantity != 0) {

        lastValues = current;
        return true;
    }
    return false;
}
