#define PULSE_RELAY 49
int slot_relays[]  = {22,23,24,25,26,27,28,29,30,31,32, 33, 34, 35, 36, 37, 38,39,40,41,42,43,44,45,46};
int button_map[]   = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,4, 5, 6, 7, 8, 9, 10,11,12};
int interuptPins[] = {18,19,20,21};
int i;
volatile int i2=0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for(i=0; i<sizeof(slot_relays);i++) {
    pinMode(slot_relays[i], OUTPUT); 
    digitalWrite(slot_relays[i], LOW);
  }
  
  pinMode(PULSE_RELAY, OUTPUT);
  digitalWrite(PULSE_RELAY, HIGH);
  
  for(i=0; i<sizeof(button_map);i++) {
    pinMode(button_map[i], INPUT);
    digitalWrite(button_map[i], HIGH);
  }
  
  for(i=0; i<sizeof(interuptPins);i++) {
    digitalWrite(interuptPins[i], HIGH);
  }
  
  attachInterrupt(2, buttonPressed2, FALLING);
//  attachInterrupt(3, buttonPressed3, FALLING);
//  attachInterrupt(4, buttonPressed4, FALLING);
//  attachInterrupt(5, buttonPressed5, FALLING);
  
  Serial.begin(19200);
}
  int i2a= 0 ; 
// the loop routine runs over and over again forever:
void loop() {

//  for(i=0; i<sizeof(slot_relays);i++) {
//      digitalWrite(PULSE_RELAY , LOW);
//      digitalWrite(slot_relays[i], HIGH);   // turn the LED on (HIGH is the voltage level)
//      delay(1000);               // wait for a second
//      digitalWrite(PULSE_RELAY, HIGH);
//      digitalWrite(slot_relays[i], LOW);    // turn the LED off by making the voltage LOW
//      delay(2000);               // wait for a second
//  }

  if(i2!=i2a){
    i2a=i2;
    int r;
    for(i=0; i<25;i++) {
      r = digitalRead(button_map[i]);
      
      if(!r){
      Serial.println(button_map[i]);
      digitalWrite(slot_relays[i], HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);               // wait for a second
      digitalWrite(slot_relays[i], LOW);    // turn the LED off by making the voltage LOW  
    }
   }
//    delay(100);
  }
}

void buttonPressed2() {
   i2 = digitalRead(21);  
}

