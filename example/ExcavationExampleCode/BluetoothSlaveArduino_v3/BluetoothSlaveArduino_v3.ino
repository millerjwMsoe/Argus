//title: BluetoothSlaveArduino_v3
//slave
//version 3
//Author: Cheyenne Phakousonh, Caroline Beavan, Joey Miller
//Updated: 5-17-19

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // rx = 10, t3 = 11

byte incomingByte, sensor1, sensor2;
byte sensor3, sensor4, sensor5, sensor6;
byte fill, mass;

void setup() {
 Serial.begin(9600);
 mySerial.begin(9600);
  //Serial.println("Meow");
 //photoresistors
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 //pinMode(10, OUTPUT);
 //pinMode(11, OUTPUT);

 delay(1000);

}

void loop() {
  Serial.println("test");
  while(mySerial.available()< 3){
    // wait for some data to be available to read
  }
  incomingByte = mySerial.read();

  if (int(incomingByte == 250)) {
    /*sensor1 = mySerial.read();
    sensor2 = mySerial.read();
    sensor3 = mySerial.read();
    sensor4 = mySerial.read();
    sensor5 = mySerial.read(); 
    sensor6 = mySerial.read();*/
    fill = mySerial.read();
    mass = mySerial.read();
    //mass varible in hectograms
    // 1 hectogram is 0.1 kilograms
    // the load cell isn't the best, so when the value goes negative, the reading will be high
    Serial.print("Fill =   ");
    Serial.println(int(fill));
    Serial.print("Mass =   ");
    Serial.println(int(mass));
      
 
    }
//changing the lights due to the photoresistors
digitalWrite(6, sensor1);
digitalWrite(7, sensor2);
digitalWrite(8, sensor3);
digitalWrite(9, sensor4);
//digitalWrite(10, sensor5);
//digitalWrite(11, sensor6);

}
