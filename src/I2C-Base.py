from smbus2 import SMBus, i2c_msg

class I2CDevice:
    def __init__(self, address, bus_num):
         self.bus_num = bus_num
         bus = SMBus(bus_num)
         self.address = address
         
    def read_from_register(self, register, offset = 0):
            try:
                READ = SMBus(self.bus_num).read_byte(register, offset)
                print(READ)
                return READ
            except:
                print(f"Unable to read from register {register}")
        
    def write_to_register(self, int, register, data, offset = 0):
        try:
            SMBus(int).write_byte_data(register, offset, data)
        except:
            print(f"Error, unable to write {data} to register {register}.")