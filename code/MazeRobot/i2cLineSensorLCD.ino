//David Schloemer 4/13/18
//Embedded Linux Spring 2018
//Program reads line locations, writes to LCD, and transmits over I2C

#include <Wire.h>
#include <LiquidCrystal.h>
#include <QTRSensors.h>

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       3000  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   10    // Pin that controls LED lights
#define SENSORSCALE   300   // Divide sensor timeout reading by
#define SENSITIVITY   2     // Line detection threshhold (timeout/sensorscale)
#define I2CADDRESS    8     // I2C address

unsigned int QTRData[NUM_SENSORS];
unsigned int QTRDataProcessed[NUM_SENSORS];

LiquidCrystal lcd(13, A1, 12, 11, A2, A3); //4-bit LCD (enable, RS, D4, D5, D6, D7)
QTRSensorsRC qtr((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9}, NUM_SENSORS, TIMEOUT, EMITTER_PIN); //QTR Sensor data pins (0, 1, 2, 3, 4, 5, 6, 7)


void setup()
{
    //Wait for setup
  delay(500);
  Serial.begin(9600);
  delay(1000);
    //begin I2C
  Wire.begin(I2CADDRESS);                // join i2c bus with address set by I2CADDRESS
  Wire.onRequest(requestEvent); // register event
    //begin LCD
  lcd.begin(16,2);
  initLCD(lcd);
    //beginQTR
  initQTR();
    //Calibrate QTR
//calibrateQTR(qtr); //QTR calibration is broken on nano

  writeBottom(lcd, "Program Begin");
}


void loop()
{
  readQTRData(); //read QTR data from sensor into QTRData

  writeTopQTR(QTRDataProcessed); //write line position to LCD

  //transmitQTRDataTest(QTRDataProcessed); //test conversion to byte
}





/***********************************  QTR Functions  ***********************************/

//QTR Sensor initialization
void initQTR()
{
  writeBottom(lcd, "QTR Init: ");
  writeBottom(lcd, "QTR Init: Done");
  delay(1000);
  return;
}

//calibrate QTR Sensor
void calibrateQTR(QTRSensorsRC sensorQTR)
{
  writeBottom(lcd, "Cal QTR: ");
  int i;
  for (i = 0; i < 100; i++)  // make the calibration take about 5 seconds
  {
    sensorQTR.calibrate();
    delay(20);
  }
  writeBottom(lcd, "Cal QTR: Done");
  delay(1000);
  return;
}

void readQTRData()
{
  qtr.read(QTRData); //read QTR sensor
  for (unsigned char i = 0; i < NUM_SENSORS; i++) //Convert QTR sensor reading to binary 1 = line 0 = no line
    {
      QTRDataProcessed[i] = (QTRData[i]/SENSORSCALE);
      if(QTRDataProcessed[i] > SENSITIVITY)
        {
          QTRDataProcessed[i] = 1;
        }
      else
        {
          QTRDataProcessed[i] = 0;
        }
      Serial.print(QTRDataProcessed[i]);
      Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    }
  Serial.println();
  return;
}
/***********************************  LCD Functions  ***********************************/
//LCD initialization
void initLCD(LiquidCrystal liquid){
analogWrite(A0, 50);
liquid.begin(16,2);
delay(10);
writeBottom(lcd, "LCD Init: ");
writeBottom(lcd, "LCD Init: Done");
delay(1000);
return;
}

//Clear top line of LCD and Write to top line of LCD
void writeTop(LiquidCrystal liquid, const char string[]){
liquid.setCursor(0,0);
delay(10);
liquid.write("                ");
liquid.setCursor(0,0);
delay(10);
liquid.write(string);
return;
}


//Clear bottom line of LCD and Write to bottom line of LCD
void writeBottom(LiquidCrystal liquid, const char string[]){
liquid.setCursor(0,1);
delay(10);
liquid.write("                ");
liquid.setCursor(0,1);
delay(10);
liquid.write(string);
delay(10);
return;
}

//Write QTR data to top line of LCD
void writeTopQTR(unsigned int QTRDataProcessed[]){
  writeTop(lcd, "    ");
  for (unsigned char i = 0; i < NUM_SENSORS; i++){
    if(QTRDataProcessed[i] == 1){
      lcd.write("1");
    }
    else{
      lcd.write("0");
    }
  }
  lcd.write("    ");
  return;
}

/***********************************  I2C Functions  ***********************************/

//event for I2C
void requestEvent() {
  writeBottom("Transmitting...");
  byte dataOut = 0;
  int j = NUM_SENSORS - 1;
  for (unsigned char i = 0; i < NUM_SENSORS; i++){
    if(QTRDataProcessed[i] == 1){
      bitSet(dataOut, j);
    }
    else{
      bitClear(dataOut, j);
    }
    j--;
  }
  Wire.write(dataOut);
  //delay(100);
  writeBottom("Transmit: Done");
  return;
}

//test for I2C byte conversion
//converts 8 element array of 1 and 0 to byte form
void transmitQTRDataTest(unsigned int QTRDataProcessed[8]){
  writeBottom("Transmit Test...");
  byte dataOut = 0;
  int j = NUM_SENSORS - 1;
  for (unsigned char i = 0; i < NUM_SENSORS; i++){
    if(QTRDataProcessed[i] == 1){
      bitSet(dataOut, j);
    }
    else{
      bitClear(dataOut, j);
    }
    j--;
  }
  Serial.println(dataOut, BIN);
  //delay(100);
  writeBottom("Transmit: Test");
  return;
}
