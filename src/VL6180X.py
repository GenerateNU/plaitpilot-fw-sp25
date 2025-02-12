from smbus2 import SMBus, i2c_msg

class VL6180X:

    def __init__(self):
        IDENTIFICATION__MODEL_ID: 0x000
        IDENTIFICATION__MODEL_REV_MAJOR: 0x001
        IDENTIFICATION__MODEL_REV_MINOR: 0x002
        IDENTIFICATION__MODULE_REV_MAJOR: 0x003
        IDENTIFICATION__MODULE_REV_MINOR: 0x004
        IDENTIFICATION__DATE_HI: 0x006
        IDENTIFICATION__DATE_LO: 0x007
        # IDENTIFICATION__TIME: 0x008
        SYSTEM__MODE_GPIO0: 0x010
        SYSTEM__MODE_GPIO1: 0x011
        SYSTEM__HISTORY_CTRL: 0x012
        SYSTEM__INTERRUPT_CONFIG_GPIO: 0x014
        SYSTEM__INTERRUPT_CLEAR: 0x015
        SYSTEM__FRESH_OUT_OF_RESET: 0x016
        SYSTEM__GROUPED_PARAMETER_HOLD: 0x017
        SYSRANGE__START: 0x018
        SYSRANGE__THRESH_HIGH: 0x019
        SYSRANGE__THRESH_LOW: 0x01A
        SYSRANGE__INTERMEASUREMENT_PERIOD: 0x01B
        SYSRANGE__MAX_CONVERGENCE_TIME: 0x01C
        SYSRANGE__CROSSTALK_COMPENSATION_RATE: 0x01E
        SYSRANGE__CROSSTALK_VALID_HEIGHT: 0x021
        SYSRANGE__EARLY_CONVERGENCE_ESTIMATE: 0x022
        SYSRANGE__PART_TO_PART_RANGE_OFFSET: 0x024
        SYSRANGE__RANGE_IGNORE_VALID_HEIGHT: 0x025
        SYSRANGE__RANGE_IGNORE_THRESHOLD: 0x026
        SYSALS__START: 0x038
        SYSALS__THRESH_HIGH: 0x03A
        SYSALS__THRESH_LOW: 0x03C
        SYSALS__INTERMEASUREMENT_PERIOD: 0x03E
        RESULT__RANGE_STATUS: 0x04D
        RESULT__ALS_STATUS: 0x04E
        RESULT__INTERRUPT_STATUS_GPIO: 0x04F
        RESULT__ALS_VAL: 0x050
        RESULT__HISTORY_BUFFER_0: 0x052
        RESULT__HISTORY_BUFFER_1: 0x054
        RESULT__HISTORY_BUFFER_2: 0x056
        RESULT__HISTORY_BUFFER_3: 0x058
        RESULT__HISTORY_BUFFER_4: 0x05A
        RESULT__HISTORY_BUFFER_5: 0x05C
        RESULT__HISTORY_BUFFER_6: 0x05E
        RESULT__HISTORY_BUFFER_7: 0x060
    
    def read_from_register(self, int, register, offset = 0):
        try:
            READ = SMBus(int).read_byte(register, offset)
            print(READ)
            return READ
        except:
            print(f"Unable to read from register {register}")
    
    def write_to_register(self, int, register, data, offset = 0):
        try:
            SMBus(int).write_byte_data(register, offset, data)
        except:
            print(f"Error, unable to write {data} to register {register}.")
        


