

#include <IRremote.h>

const long KEY= 0xFF6897;
const long CODE =0xFFA25D;
const int buttonPin = 4; 


int RECV_PIN = 11;
int buttonState = 0; 
int state = 0;
IRsend irsend;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() 
{


  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) 
  {
      Serial.println("[INF]Ask for code");
      irsend.sendNEC(KEY, 32);
      delay(40);
      irrecv.enableIRIn();
      state = 1;
  }
  
  if (state==1 && irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
   
    switch (results.value)
      {
        case CODE:
         Serial.println("[CONF] CODE RECIVE");
         irsend.sendNEC(0xFFAAAA, 32);
         Serial.println("[INF]Send OK confirmation");
         state = 0;
         delay(40);
         irrecv.enableIRIn();
         break;
      }
      irrecv.resume();
  }
  delay(100);
}
