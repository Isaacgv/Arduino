

#include <IRremote.h>

const long KEY = 0xFF6897;

int RECV_PIN = 11;

IRsend irsend;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() 
{
  
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
   
    switch (results.value)
      {
        case KEY:
         Serial.println("[CONF]SOLICITATION RECIVE");
         irsend.sendNEC(0xFFA25D, 32);
         Serial.println("[INF]Send Code");
         delay(40);
         irrecv.enableIRIn();
         break;
      }
      irrecv.resume();
  }
  delay(100);
}
