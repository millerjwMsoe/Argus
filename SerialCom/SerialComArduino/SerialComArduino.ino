void setup(){
  Serial.begin(9600); // baud rate = 9600
}

void loop(){
  for(int i = 1; i < 255; i++){
    Serial.print("Messages sent: ");
    Serial.println(i);
    delay(500); // wait 500ms
  }
}
