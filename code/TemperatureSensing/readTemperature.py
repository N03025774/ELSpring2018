#!/usr/bin/python
import os
import time
import sqlite3 as mydb
import sys


def readTemp():
    "Read temperature from serial thermometer"
    tempfile = open("/sys/bus/w1/devices/28-0000069816ee/w1_slave")
    tempfile_text = tempfile.read()
    currentTime = time.strftime('%x %X %Z')
    tempfile.close()
    tempC = float(tempfile_text.split("\n")[1].split("t=")[1])/1000
    tempF = tempC*9.0/5.0+32.0
    return [currentTime, tempC, tempF];

print("readTemperature is "),
print(readTemp())
