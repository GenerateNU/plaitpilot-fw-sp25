#include <Arduino.h>
#include <Wire.h>
#include <iostream>

#define SDA_PIN 4
#define SCL_PIN 5
#define GPIO_PIN 6
#define SLAVE_ADDRESS 0x29

using namespace std;

class VL6180X {    
    public:
        uint16_t IDENTIFICATION__MODEL_ID = 0x000; // Register Adddress for VL6180X
        uint16_t IDENTIFICATION__MODEL_REV_MAJOR = 0x001;
        uint16_t IDENTIFICATION__MODEL_REV_MINOR = 0x002;
        uint16_t IDENTIFICATION__MODULE_REV_MAJOR = 0x003;
        uint16_t IDENTIFICATION__MODULE_REV_MINOR = 0x004;
        uint16_t IDENTIFICATION__DATE_HI = 0x006;
        uint16_t IDENTIFICATION__DATE_LO = 0x007;
        uint16_t IDENTIFICATION__TIME = 0x008;

        uint16_t SYSTEM__MODE_GPIO0 = 0x010;
        uint16_t SYSTEM__MODE_GPIO1 = 0x011;
        uint16_t SYSTEM__HISTORY_CTRL = 0x012;
        uint16_t SYSTEM__INTERRUPT_CONFIG_GPIO = 0x014;
        uint16_t SYSTEM__INTERRUPT_CLEAR = 0x015;
        uint16_t SYSTEM__FRESH_OUT_OF_RESET = 0x016;
        uint16_t SYSTEM__GROUPED_PARAMETER_HOLD = 0x017;

        uint16_t SYSRANGE__START = 0x018;
        uint16_t SYSRANGE__THRESH_HIGH = 0x019;
        uint16_t SYSRANGE__THRESH_LOW = 0x01A;
        uint16_t SYSRANGE__INTERMEASUREMENT_PERIOD = 0x01B;
        uint16_t SYSRANGE__MAX_CONVERGENCE_TIME = 0x01C;
        uint16_t SYSRANGE__CROSSTALK_COMPENSATION_RATE = 0x01D;
        uint16_t SYSRANGE__CROSSTALK_VALID_HEIGHT = 0x01E;
        uint16_t SYSRANGE__EARLY_CONVERGENCE_ESTIMATE = 0x01F;

        uint16_t SYSALS__START = 0x038;
        uint16_t SYSALS__THRESH_HIGH = 0x03A;
        uint16_t SYSALS__THRESH_LOW = 0x03C;
        uint16_t SYSALS__INTERMEASUREMENT_PERIOD = 0x03E;
        uint16_t SYSALS__ANALOGUE_GAIN = 0x03F;
        uint16_t SYSALS__INTEGRATION_PERIOD = 0x040;

        uint16_t RESULT__RANGE_STATUS = 0x04D;
        uint16_t RESULT__ALS_STATUS = 0x04E;
        uint16_t RESULT__INTERRUPT_STATUS_GPIO = 0x04F;
        uint16_t RESULT__ALS_VAL = 0x050;
        uint16_t RESULT__RANGE_VAL = 0x062;
        uint16_t RESULT__RANGE_RAW = 0x064;

        uint16_t READOUT__AVERAGING_SAMPLE_PERIOD = 0x10A;
        uint16_t FIRMWARE__BOOTUP = 0x119;
        uint16_t FIRMWARE__RESULT_SCALER = 0x120;
        uint16_t I2C_SLAVE__DEVICE_ADDRESS = 0x212;
        uint16_t INTERLEAVED_MODE__ENABLE = 0x2A3;

        uint8_t read8BitRegister(uint16_t reg) // Reads a value from an 8-bit register
        {
            Wire.beginTransmission(SLAVE_ADDRESS); // start bit
            
            Wire.write((reg >> 8) & 0xFF);  // High byte
            Wire.write(reg & 0xFF);         // Low byte


            Wire.endTransmission(); // stop bit

            Wire.requestFrom(SLAVE_ADDRESS, 1); // requests 1 byte from the slave
            
            if (Wire.available() >= 1) // if the number of bytes available is greater than or equal to the number of requested bytes (1)
            {
                uint8_t data = Wire.read();
                Serial.println(data);
                return data;
            }
            else
            {
                Serial.println("Error: Unable to read from the VL6180X");
                return 0;
            }
        }

        uint16_t read16BitRegister(uint16_t reg)
        {
            Wire.beginTransmission(SLAVE_ADDRESS); // start bit

            Wire.write((reg >> 8) & 0xFF);  // High byte
            Wire.write(reg & 0xFF);         // Low byte

            Wire.endTransmission(); // stop bit

            Wire.requestFrom(SLAVE_ADDRESS, 2); // requests 2 bytes from the slave
            if (Wire.available() >= 2) // if the number of bytes available is greater than or equal to the number of requested bytes (2)
            {
                uint16_t data = (uint16_t)Wire.read() << 8;
                data |= Wire.read();
            }
            else
            {
                Serial.println("Error: Unable to read from the VL6180X");
                return 0;
            }
        }

        uint32_t read32BitRegister(uint16_t reg)
        {
            Wire.beginTransmission(SLAVE_ADDRESS); // start bit

            Wire.write((reg >> 8) & 0xFF);  // High byte
            Wire.write(reg & 0xFF);         // Low byte

            Wire.endTransmission(); // stop bit

            Wire.requestFrom(SLAVE_ADDRESS, 4); // requests 4 bytes from the slave
            if (Wire.available() >= 4) // if the number of bytes available is greater than or equal to the number of requested bytes (4)
            {
                uint32_t data = (uint32_t)Wire.read() << 24;
                data |= (uint32_t)Wire.read() << 16;
                data |= (uint16_t)Wire.read() << 8;
                data |= Wire.read();
            }
            else
            {
                Serial.println("Error: Unable to read from the VL6180X");
                return 0;
            }
        }

        void write8BitRegister(uint16_t reg, uint8_t data)
        {
            Wire.beginTransmission(SLAVE_ADDRESS); // start bit

            Wire.write((reg >> 8) & 0xFF);  // High byte
            Wire.write(reg & 0xFF);         // Low byte

            Wire.write(data);

            Wire.endTransmission();
        }

        void write16BitRegister(uint16_t reg, uint16_t data)
        {
            Wire.beginTransmission(SLAVE_ADDRESS); // start bit

            Wire.write((reg >> 8) & 0xFF);  // High byte
            Wire.write(reg & 0xFF);         // Low byte

            Wire.write((uint8_t)(data) >> 8);
            Wire.write((uint8_t)(data) >> 0);

            Wire.endTransmission();
        }

        void write32BitRegister(uint16_t reg, uint32_t data)
        {
            Wire.beginTransmission(SLAVE_ADDRESS); // start bit

            Wire.write((reg >> 8) & 0xFF);  // High byte
            Wire.write(reg & 0xFF);         // Low byte

            Wire.write((uint8_t)(data) >> 24);
            Wire.write((uint8_t)(data) >> 16);
            Wire.write((uint8_t)(data) >> 8);
            Wire.write((uint8_t)(data) >> 0);

            Wire.endTransmission();
        }
    };

VL6180X Sensor;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    uint8_t MODEL_ID = Sensor.read8BitRegister(Sensor.IDENTIFICATION__MODEL_ID);
    Serial.println(MODEL_ID);
}

void loop()
{

}

