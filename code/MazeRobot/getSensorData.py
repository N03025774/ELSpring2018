import smbus
import time
bus = smbus.SMBus(0)
address = 0x08

def linePosition():
        print "Getting Line Pos..."
        position = bus.read_byte_data(address, 1)
        print "Got line Pos"
        return position


while True:
        print "Line Position Test"
        position = linePosition()     #this returns the value to 1 decimal place in degrees.
        print bin(bearing)
        time.sleep(2)