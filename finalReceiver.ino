// RF Link using VirtualWire to receive messages
// simplex (one-way) receiver with a 315MHz RF Link Receiver module
// rx pin 23 on mega

#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder
#undef int
#undef abs
#undef double
#undef float
#undef round

int lvl_one_on = 65;
int lvl_two_on = 66;
int lvl_three_on = 67;
int lvl_one_off = 97;
int lvl_two_off = 98;
int lvl_three_off = 99;

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

void setup()
{
    pinMode(one, OUTPUT);
    pinMode(two, OUTPUT);
    pinMode(three, OUTPUT);  
    Serial.begin(9600);    

// Initialise the IO and ISR
   // Required for RX Link Module
   vw_set_ptt_inverted(true); 
    vw_setup(2400);                   // Bits per sec
    vw_set_rx_pin(8);           // We will be receiving on pin 23 (Mega) ie the RX pin from the module connects to this pin. 
    vw_rx_start();                      // Start the receiver 
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // check to see if anything has been received
    {
        Serial.print(buf[0]);  // the received data is stored in buffer
        if (buf[0] == lvl_one_on){
          vib_one(true);
        }
        else if (buf[0] == lvl_two_on){
         vib_two(true); 
        }
        else if (buf[0] == lvl_three_on){
         vib_three(true);
        }
        else if (buf[0] == lvl_one_off){
          vib_one(false);
        }
        else if (buf[0] == lvl_two_off){
          vib_two(false);
        }
        else if (buf[0] == lvl_three_off){
          vib_three(false);
        }
    Serial.println("");
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


