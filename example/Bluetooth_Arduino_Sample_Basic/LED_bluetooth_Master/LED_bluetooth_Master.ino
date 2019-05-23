//master

//#define button 8
//int buttonState = 0;

void setup() { 
  pinMode(button, INPUT);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
// delay(100);
// buttonState = digitalRead(button);
// if (buttonState == HIGH) {
//   Serial.print('1'); // Sends '1' to serialout
// }
// else {
//   Serial.print('0');
// }  

//Just sends 1, 0, or 2.

Serial.print('1');
delay(1000);
Serial.print('0');
delay(1000);
Serial.print('2');
delay(1000);
}
