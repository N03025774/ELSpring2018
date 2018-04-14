#David Schloemer 4/13/18
#Embedded Linux Spring 2018
#This program reads a byte of data from an i2c device
#In this case I am reading an 8 bit value, each bit indicates if there is a line beneath the sensor. The bit will be 1 if there is a line beneath the sensor.
#You must also enable i2c on Pi using
#sudo raspi-config
#>5 Interface Options
#>P5 I2C
#>Yes

import smbus         #i2c pyton interface library
import time          #for delays
bus = smbus.SMBus(1) #i2c bus of Pi
address = 0x08       #address of arduino (set in arduino code)

#This function reads the data from arduino via i2c and returns a single byte
def getLinePosition():
        print "Getting Line Pos..."
        position = bus.read_byte_data(address, 1) #request byte from arduino
        print "Got line Pos"
        return position

#This function returns state of sensor at (sensor) using string address/sensor #(0-7)
def getLineState(sensor):
        stringPosition = '{0:08b}'.format(position) #assigns position(an integer) to an addressable string array in binary format.
        return stringPosition[sensor]

#Main function
while True:
        print "Line Position Test:"
        position = getLinePosition()    #read data from arduino

        for x in range (0, 8):          #this for loop shows iteration through string
		          print getLineState(x),#the , indicated values should print next to each other

        print "\n"                      #new line after all values are read

        #print '{0:08b}'.format(position) #print as binary value
        time.sleep(1)                     #wait 1s before next read
