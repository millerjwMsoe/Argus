//all photoresistors
//serial communication
//master

int S1, S2, log1, log2;
int S3, S4, log3, log4;
int S5, S6, log5, log6;
byte p1, p2, p3, p4, p5, p6;

void setup() {
Serial.begin(9600);

}

void loop() {
  delay(1000);
log1 = analogRead(0);
log2 = analogRead(1);
log3 = analogRead(2);
log4 = analogRead(3);
log5 = analogRead(4);
log6 = analogRead(5);
//Serial.println(log1);
//Serial.println(log2);
//remap values
p1 = map(log1, 0, 1000, 0, 249);
p2 = map(log2, 0, 1000, 0, 249);
p3 = map(log3, 0, 1000, 0, 249);
p4 = map(log4, 0, 1000, 0, 249);
p5 = map(log5, 0, 1000, 0, 249);
p6 = map(log6, 0, 1000, 0, 249);

Serial.write(250);
Serial.write(p1);
//Serial.println(p1);
//delay(10);
//Serial.write(251);
Serial.write(p2);
//Serial.println(p2);
//delay(10);

//Serial.write(252);
Serial.write(p3);
//delay(10);

//Serial.write(253);
Serial.write(p4);
//delay(10);

//Serial.write(254);
Serial.write(p5);
//delay(10);

//Serial.write(255);
Serial.write(p6);
//delay(10);


}
