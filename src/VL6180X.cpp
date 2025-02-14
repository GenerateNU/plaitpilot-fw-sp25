#include <Arduino.h>
#include <Wire.h>

using namespace std;

class VL6180X {
    private:
        uint8_t IDENTIFICATION__MODEL_ID = 0x000;
        uint8_t IDENTIFICATION__MODEL_REV_MAJOR = 0x001;
        uint8_t IDENTIFICATION__MODEL_REV_MINOR = 0x002;
        uint8_t IDENTIFICATION__MODULE_REV_MAJOR = 0x003;
        uint8_t IDENTIFICATION__MODULE_REV_MINOR = 0x004;
        uint8_t IDENTIFICATION__DATE_HI = 0x006;
        uint8_t IDENTIFICATION__DATE_LO = 0x007;
        uint16_t IDENTIFICATION__TIME = 0x008;

        uint8_t SYSTEM__MODE_GPIO0 = 0x010;
        uint8_t SYSTEM__MODE_GPIO1 = 0x011;
        uint8_t SYSTEM__HISTORY_CTRL = 0x012;
        uint8_t SYSTEM__INTERRUPT_CONFIG_GPIO = 0x014;
        uint8_t SYSTEM__INTERRUPT_CLEAR = 0x015;
        uint8_t SYSTEM__FRESH_OUT_OF_RESET = 0x016;
        uint8_t SYSTEM__GROUPED_PARAMETER_HOLD = 0x017;

        uint8_t SYSRANGE__START = 0x018;
        uint8_t SYSRANGE__THRESH_HIGH = 0x019;
        uint8_t SYSRANGE__THRESH_LOW = 0x01A;
        uint8_t SYSRANGE__INTERMEASUREMENT_PERIOD = 0x01B;
        uint8_t SYSRANGE__MAX_CONVERGENCE_TIME = 0x01C;
        uint8_t SYSRANGE__CROSSTALK_COMPENSATION_RATE = 0x01D;
        uint8_t SYSRANGE__CROSSTALK_VALID_HEIGHT = 0x01E;
        uint8_t SYSRANGE__EARLY_CONVERGENCE_ESTIMATE = 0x01F;

        uint8_t SYSALS__START = 0x038;
        uint8_t SYSALS__THRESH_HIGH = 0x03A;
        uint8_t SYSALS__THRESH_LOW = 0x03C;
        uint8_t SYSALS__INTERMEASUREMENT_PERIOD = 0x03E;
        uint8_t SYSALS__ANALOGUE_GAIN = 0x03F;
        uint8_t SYSALS__INTEGRATION_PERIOD = 0x040;

        uint8_t RESULT__RANGE_STATUS = 0x04D;
        uint8_t RESULT__ALS_STATUS = 0x04E;
        uint8_t RESULT__INTERRUPT_STATUS_GPIO = 0x04F;
        uint8_t RESULT__ALS_VAL = 0x050;
        uint8_t RESULT__RANGE_VAL = 0x062;
        uint8_t RESULT__RANGE_RAW = 0x064;

        uint8_t READOUT__AVERAGING_SAMPLE_PERIOD = 0x10A;
        uint8_t FIRMWARE__BOOTUP = 0x119;
        uint8_t FIRMWARE__RESULT_SCALER = 0x120;
        uint8_t I2C_SLAVE__DEVICE_ADDRESS = 0x212;
        uint8_t INTERLEAVED_MODE__ENABLE = 0x2A3;

    public:
        uint8_t getSlaveAddress()
        {
            Wire.requestFrom(I2C_SLAVE__DEVICE_ADDRESS, 7);
            uint8_t SLAVE_ADDRESS = Wire.read();
            return SLAVE_ADDRESS;
        }
        

};

int main() 
{
    Wire.begin();
    getSlaveAddress();
    Wire.beginTransmission(SLAVE_ADDRESS);

    Wire.endTransmission();
}

