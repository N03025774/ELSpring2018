#!/usr/bin/python
#import os
#import time
import sqlite3 as mydb
#import sys

from readTemperature import readTemp

def logTemp():
   con = mydb.connect('/home/dave/ELSpring2018/code/TemperatureSensing/temperature.db')
   with con:
     try:
       [t,C,F]=readTemp()
       print("Current temperature is: %s F" %F)
       cur = con.cursor()
       #sql = "insert into TempData values(?,?,?)"
       cur.execute('insert into TempData values(?,?,?)', (t,C,F))
       print "Temperature logged"
     except:
       print "Error!!"
