int counter = 0;
int incomingByte;

int one = 5;
int two = 7;
int three = 9;

boolean one_act = false;
boolean two_act = false;
boolean three_act = false;

long timer_one;
long timer_two;
long timer_three;

long delayTime = 5000;


#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder


void setup()
{
  Serial.begin(115200);

  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);  

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for RF Link module
  vw_setup(2400);                 // Bits per sec
  vw_set_tx_pin(8);                // pin 3 is used as the transmit data out into the TX Link module, change this to suit your needs. 
}

void loop()
{
  const char *msgA = "A";
  const char *msgB = "B";
  const char *msgC = "C";
  const char *msga = "a";
  const char *msgb = "b";
  const char *msgc = "c";

  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    
    //set counter based on bluetooth message
    //left arm
    if (incomingByte == 'A') {
      Serial.println("LEFT1 ON");
      counter=1;
    }
    else if (incomingByte == 'B') {
      Serial.println("LEFT2 ON");
      counter=2;
    }
    else if (incomingByte == 'C') {
      Serial.println("LEFT3 ON");
      counter=3;
    }
    else if (incomingByte == 'a') {
      Serial.println("LEFT1 OFF");
      counter=4;
    }
    else if (incomingByte == 'b') {
      Serial.println("LEFT2 OFF");
      counter=5;
    }
    else if (incomingByte == 'c') {
      Serial.println("LEFT3 OFF");
      counter=6;
    }
    
    //right arm
    else if (incomingByte == 'D') {
      Serial.println("RIGHT1 ON");
      counter=7;
    }
    else if (incomingByte == 'E') {
      Serial.println("RIGHT2 ON");
      counter=8;
    }
    else if (incomingByte == 'F') {
      Serial.println("RIGHT3 ON");
      counter=9;
    }
    else if (incomingByte == 'd') {
      Serial.println("RIGHT1 OFF");
      counter=10;
    }
    else if (incomingByte == 'e') {
      Serial.println("RIGHT2 OFF");
      counter=11;
    }
    else if (incomingByte == 'f') {
      Serial.println("RIGHT3 OFF");
      counter=12;
    }
    
    //left arm counters
    if (counter == 1){
      vw_send((uint8_t *)msgA, strlen(msgA));
      vw_wait_tx(); 
      Serial.println("send A");
      counter = 0;
    }
    else if (counter == 2){
      vw_send((uint8_t *)msgB, strlen(msgB));
      vw_wait_tx(); 
      Serial.println("send B");
      counter = 0;
    }
    else if (counter == 3){
      vw_send((uint8_t *)msgC, strlen(msgC));
      vw_wait_tx(); 
      Serial.println("send C");
      counter = 0;
    }
    else if (counter == 4){
      vw_send((uint8_t *)msga, strlen(msga));
      vw_wait_tx(); 
      Serial.println("send a");
      counter = 0;
    }
    else if (counter == 5){
      vw_send((uint8_t *)msgb, strlen(msgb));
      vw_wait_tx(); 
      Serial.println("send b");
      counter = 0;
    }
    else if (counter == 6){
      vw_send((uint8_t *)msgc, strlen(msgc));
      vw_wait_tx(); 
      Serial.println("send c");
      counter = 0;
    }
    
    //right arm counters
    else if (counter == 7){
      vib_one(true);
      counter = 0;
    }
    else if (counter == 8){
      vib_two(true);
      counter = 0;
    }
    else if (counter == 9){
      vib_three(true);
      counter = 0;
    }
     else if (counter == 10){
      vib_one(false);
      counter = 0;
    }
     else if (counter == 11){
      vib_two(false);
      counter = 0;
    }
     else if (counter == 12){
      vib_three(false);
      counter = 0;
    }
  }
  
  if (one_act && millis() > timer_one + delayTime){
   vib_one(false); 
  }
  if (two_act && millis() > timer_two + delayTime){
   vib_two(false); 
  }
  if (three_act && millis() > timer_three + delayTime){
   vib_three(false); 
  }
}
void vib_one(boolean state){
  if (state == true){
    if(one_act == false){
      timer_one = millis();
      one_act = true;
      digitalWrite(one, HIGH);
    }
  }
  else if(state == false){
    if(one_act == true){
      one_act = false;
      digitalWrite(one, LOW);
    }
  }
}
void vib_two(boolean state){
  if (state == true){
    if(two_act == false){
      timer_two = millis();
      two_act = true;
      digitalWrite(two, HIGH);
    }
  }
  else if(state == false){
    if(two_act == true){
      two_act = false;
      digitalWrite(two, LOW);
    }
  }
}
void vib_three(boolean state){
  if (state == true){
    if(three_act == false){
      timer_three = millis();
      three_act = true;
      digitalWrite(three, HIGH);
    }
  }
  else if(state == false){
    if(three_act == true){
      three_act = false;
      digitalWrite(three, LOW);
    }
  }
}


