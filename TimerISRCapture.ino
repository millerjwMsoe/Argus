
bool blink = true;
int numOverflow = 0;
double t5c = 1024.0/1600000000.0;
unsigned long tstart, tstop, dcount;

ISR(TIMER5_CAPT_vect){
  tstop = ICR5; // this is the timer count when capture occured
  dcount = (0x10000*numOverflow)-tstart+tstop; // magic
  Serial.print("Ticks: ");
  Serial.println(dcount);
  Serial.print("Seconds: ");
  double timeSec = dcount * t5c;
  Serial.println(timeSec);
   
  if(blink){
    digitalWrite(3,HIGH);
    blink = false;
  } else {
    digitalWrite(3,LOW);
    blink = true;
  }
  
  numOverflow = 0; // reset overflows for next operation
}

ISR(TIMER5_OVF_vect){
  numOverflow ++;
  //Serial.print("Overflow #");
  //Serial.println(numOverflow);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
   pinMode(48, INPUT);
   Serial.begin(9600);
   TIMSK5 = (TIMSK5 & B11011110) | 0x21; //enable timer capture interrupt and overflow interrupt
   TCCR5B = (TCCR5B & B10111000) | 0x45; //falling edge, 1024 prescale
}

void loop() {
  // put your main code here, to run repeatedly:

}
