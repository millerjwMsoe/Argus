/*
 * Wiring for Hall effect sensors
 * Internal pull up resistors are enabled for each pin so only the data line will need to be connected
 * to the desired pin. the input pints for hall effect sensors are 18-21.
 * 
 * 
 */
const byte ipin1 = 18;
const byte ipin2 = 19;
const byte ipin3 = 20;
const byte ipin4 = 21;

int ipin1Count = 0, ipin2Count = 0, ipin3Count = 0, ipin4Count = 0;
int rpm1, rpm2, rpm3, rpm4;
const double sampleIntervalms = 5000;
const double msToMin = 60000;
const double countToRPM = msToMin / sampleIntervalms;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   
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
  // put your main code here, to run repeatedly:
  
  delay(sampleIntervalms);
  noInterrupts();

  rpm1 = ipin1Count * countToRPM;
  rpm2 = ipin2Count * countToRPM;
  rpm3 = ipin3Count * countToRPM;
  rpm4 = ipin4Count * countToRPM;
  
  Serial.print("RPM 1: ");
  Serial.println(rpm1);
  Serial.print("RPM 2: ");
  Serial.println(rpm2);
  Serial.print("RPM 3: ");
  Serial.println(rpm3);
  Serial.print("RPM 4: ");
  Serial.println(rpm4);
  
  ipin1Count = 0;
  ipin2Count = 0;
  ipin3Count = 0;
  ipin4Count = 0;
  interrupts();
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

