//title: BluetoothMasterArduino_v3
//all photoresistors and the load cell
//serial communication
//master
//version 3
//please grab the HX-711 master library in the Github. Do not download the one 
//from online or in the Arduino libraries
//Author: Cheyenne Phakousonh, Caroline Beavan, Joey Miller

//m will be 10 deca grams (1kg = 10 hecto grams.)
// 0.1 kg = 1 hectograms
// 1 kg = 10 hectograms
//10 kg = 100 hectograms

//Updated: 5-17-19
#include <HX711.h>

#define calibration_factor -6000 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  6
#define CLK  5

int S1, S2, log1, log2;
int S3, S4, log3, log4;
int S5, S6, log5, log6;
byte fill, ma;
float mass, m;
HX711 scale(DOUT, CLK);

void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() {
  delay(1000);
  log1 = analogRead(0);
  log2 = analogRead(1);
  log3 = analogRead(2);
  log4 = analogRead(3);
  log5 = analogRead(4);
  log6 = analogRead(5);
  
  //Photoresistor 1 at A0 is the one at the bottom.
  if(log1 < 100){
    S1 = 1;
  } else {//the light is on if it is full.
    S1 = 0;
  }
  
  if(log2 < 100){
    S2 = 1;
  } else { //the light is on if it is full.
    S2 = 0;
  }
  
  if(log3 < 100){
    S3 = 1;
  } else { //the light is on if it is full.
    S3 = 0;
  }
  
  if(log4 < 100){
    S4 = 1;
  } else {  //the light is on if it is full.
    S4 = 0;
  }
  
  if(log5 < 100){
    S5 = 1;
  } else { //the light is on if it is full.
    S5 = 0;
  }
  
  if(log6 < 100){
    S6 = 1;
  } else {  //the light is on if it is full.
    S6 = 0;
  }
  
  //for fill
  // The fill value will be based on the highest 
  //fill of the bucket.
  if(S6){
    fill = 100;
  } else if(S5){
    fill = 83;
  } else if(S4){
    fill = 67;
  } else if(S3){
    fill = 50;
  } else if(S2){
    fill = 33;
  } else if(S1){
    fill = 17;
  } else {
    fill = 0;
  }
 
  //mass
  mass = scale.get_units(); //scale.get_units() returns a float
    //Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
    //mass units in 0.1kgs
  m = mass*10;

  ma = (byte)m;
    //changes m to bytes input as hecto grams.
  //Serial.println("           ");
  //Serial.println(scale.get_units(), 1);  
  //Serial.println(mass);
  //Serial.println(m);
  //Serial.println(ma);
  //commented code to verify the mass values.
  
  Serial.write(250); //incoming first byte
  Serial.write(fill); // value between 0 and 100. percentage fill of bucket 
  Serial.write(ma); // value between 0 and 100. units are hectograms  
}
