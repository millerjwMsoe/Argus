/*
 * Wiring for Hall effect sensors
 * Internal pull up resistors are enabled for each pin so only the data line will need to be connected
 * to the desired pin. the input pints for hall effect sensors are 18-21.
 * 
 * Wheel to sensor map is as follows
 * Left Front (LF) = sensor 1 = pin 18
 * Right Front (RF) = sensor 2 = pin 19
 * Right Rear (RR) = sensor 3 = pin 20
 * Left Rear (LR) = sensor 4 = pin 21
 * 
 * Proximity sensor is connected to I2C lines and measures in mm
 * 
 * Weight sensor and Volume detection are done via other arduino
 * and are transmitted by bluetooth
 * 
 * Libraries to include:  VL53L1X by sparkfun V 
 *                        ArduinoJson V6.10
 */

#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "SparkFun_VL53L1X.h"

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

SFEVL53L1X distanceSensor;
SoftwareSerial mySerial(10,11);

const byte ipin1 = 18;
const byte ipin2 = 19;
const byte ipin3 = 20;
const byte ipin4 = 21;

int ipin1Count = 0, ipin2Count = 0, ipin3Count = 0, ipin4Count = 0;
int rpm1, rpm2, rpm3, rpm4;
int distance1, distance2;
double volume; // units are in something...
double mass; // units again are something...
const double sampleIntervalms = 1000;
const double msToMin = 60000;
const double numMagnets = 1; // change this one to allow for more  poles to be placed on wheel
const double countToRPM = msToMin / sampleIntervalms / numMagnets;

StaticJsonDocument<200> doc;

void setup() {
  // put your setup code here, to run once:

  Wire.begin(); // I2C line to proximity sensor
  Serial.begin(9600); // serial port to RPI
  mySerial.begin(9600); // bluetooth module

  //if (distanceSensor.begin() == false)
  //{
  //  Serial.println("Sensor online!");
  //}

  // Initialize pins for Hall effect sensors.
  pinMode(ipin1, INPUT_PULLUP);
  pinMode(ipin2, INPUT_PULLUP);
  pinMode(ipin3, INPUT_PULLUP);
  pinMode(ipin4, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(ipin1), ipin1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(ipin2), ipin2ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(ipin3), ipin3ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(ipin4), ipin4ISR, FALLING);
}


void loop() {
  
  delay(sampleIntervalms);
  byte incomingByte;

  // if there is no bluetooth data available volume and mass remain the same
  while(mySerial.available() > 3){ // must be atleast one packet of data in stream
    incomingByte = mySerial.read();
    if(((int)incomingByte) == 250){    // start byte of message
      volume = (int)mySerial.read();
      mass = (int)mySerial.read();
      mass = mass / 10.0;       // convert back to kg
      //Serial.println(volume);
      //Serial.println(mass);
    }
  }

  // get new priximity data in units mm
  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
  distance1 = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.stopRanging();

  //Serial.print("Distance(mm): ");
  //Serial.println(distance);

  // disable interrupts and get new rpm data
  noInterrupts();
  rpm1 = ipin1Count * countToRPM;
  rpm2 = ipin2Count * countToRPM;
  rpm3 = ipin3Count * countToRPM;
  rpm4 = ipin4Count * countToRPM;
  ipin1Count = 0;
  ipin2Count = 0;
  ipin3Count = 0;
  ipin4Count = 0;
  interrupts();
  
  //int distance = 112;
  distance1 = -4; 
  distance2 = 0;
  doc["DIST1"] = distance1; // distance in mm
  doc["DIST2"] = distance2; // distance in mm
  doc["LF_RPM"] = rpm1;
  doc["RF_RPM"] = rpm2;
  doc["RR_RPM"] = rpm3;
  doc["LR_RPM"] = rpm4;
  doc["VOLUME"] = volume;
  doc["MASS"] = mass;

  serializeJson(doc, Serial);
  Serial.println(); // new line character to seperate the messages.
  Serial.flush();
}

void ipin1ISR(){
  ipin1Count++;
}

void ipin2ISR(){
  ipin2Count++;
}

void ipin3ISR(){
  ipin3Count++;
}

void ipin4ISR(){
  ipin4Count++;
}
