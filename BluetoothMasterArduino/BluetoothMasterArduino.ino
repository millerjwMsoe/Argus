//master
//Photoresisitor 1

int S1, S2, p1, p2, log1, log2;

void setup() {
Serial.begin(9600);

}

void loop() {
log1 = analogRead(0);
log2 = analogRead(1);
//Serial.println(log1);
//Serial.println(log2);
//remap values
p1 = map(log1, 0, 1000, 0, 253);
p2 = map(log2, 0, 1000, 0, 253);

Serial.write(254);
Serial.write(p1);
//Serial.println(p1);
delay(1000);
Serial.write(255);
Serial.write(p2);
//Serial.println(p2);

delay(150);


}
