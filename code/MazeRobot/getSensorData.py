#David Schloemer
#Embedded Linux Spring 2018
#This program reads a byte of data from an i2c device
#In this case I am reading an 8 bit value, each bit indicates if there is a line beneath the sensor. The bit will be 1 if there is a line beneath the sensor.

import smbus         #i2c pyton interface
import time
bus = smbus.SMBus(1) #i2c bus
address = 0x08       #address of arduino

def getLinePosition():
        print "Getting Line Pos..."
        position = bus.read_byte_data(address, 1) #request byte from arduino
        print "Got line Pos"
        return position

#returns state of sensor at (sensor) using string address/sensor #(0-7)
def getLineState(sensor): #needs testing
        stringPosition = '{0:08b}'.format(position) #needs testing
        return stringPosition[sensor]


while True:
        print "Line Position Test"
        position = getLinePosition()

        print '{0:08b}'.format(position) #print as binary value
        time.sleep(2)
