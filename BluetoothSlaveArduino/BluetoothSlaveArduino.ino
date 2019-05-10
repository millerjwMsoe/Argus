#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // rx = 3, t3 = 4

byte incomingByte, sensor1, sensor2;
byte sensor3, sensor4, sensor5, sensor6;


void setup() {
 Serial.begin(9600);
 //Serial.println("Ready");
  mySerial.begin(9600);
  Serial.println("Meow");
 //photoresistors
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);

 delay(1000);

}

void loop() {
  while(mySerial.available()< 7){
    // wait for some data to be available to read
  }
//if(Serial.available()){  //any bytes available?
  incomingByte = mySerial.read();
  //Serial.println(int(incomingByte));
  //delay(10);
  if (int(incomingByte == 250)) {
    sensor1 = mySerial.read();
    Serial.print("Sensor 1 ="); 
    Serial.println(int(sensor1));
  //}
  //delay(10);
  //if((int(incomingByte) == 251)) {
    sensor2 = mySerial.read();
    Serial.print("Sensor 2 =");    
    Serial.println(int(sensor2));
    
  //}

  //delay(10);
  //if((int(incomingByte) == 252)) {
    sensor3 = mySerial.read();
    Serial.print("Sensor 3 =");    
    Serial.println(int(sensor3));
    
  //}
  //delay(10);
  //if((int(incomingByte) == 253)) {
    sensor4 = mySerial.read();
    Serial.print("Sensor 4 =");    
    Serial.println(int(sensor4)); 
  //}
    
  //delay(100);
  //if((int(incomingByte) == 254)) {
    sensor5 = mySerial.read();
    Serial.print("Sensor 5 =");    
    Serial.println(int(sensor6));    
  //}

  //delay(10);
  //if((int(incomingByte) == 255)) {
    sensor6 = mySerial.read();
    Serial.print("Sensor 6 =");    
    Serial.println(int(sensor6));    
  //}
}

analogWrite(6, sensor1);
analogWrite(7, sensor2);
analogWrite(8, sensor3);
analogWrite(9, sensor4);
analogWrite(10, sensor5);
analogWrite(11, sensor6);
//delay(150);
}
