//This is Second Version of the remote.
//In this I am using
// 1) Simple on and off switch feature.
// 2) One Power button switch to off all but one switch

#include <IRremote.h>

int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;
// Initializing the pins for Relay
int Relay1 = 2;
int Relay2 = 3;
int Relay3 = 4;
int Relay4 = 5;
// Inializing the variable for storing the last status of Relay_pins
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int dt = 60;
int dt2=100;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, HIGH);//HIGH means off
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
}
void loop()

{

  while (irrecv.decode(&results) == 0) {
  }
  Serial.println(results.value, HEX);
  delay(dt2);
  irrecv.resume();
  /*  if (irrecv.decode(&results))
    {
      Serial.println(results.value, HEX); // Print the Serial 'results.value'
      irrecv.resume();   // Receive the next value
      delay(dt);
    }
  */

  if (results.value == 0x1FE50AF)
  {
    val1 = digitalRead(Relay1);
    if (val1 == 0)
    {
      digitalWrite(Relay1, HIGH);
      val1 = 1;
      delay(dt);
    }
    else
    {
      digitalWrite(Relay1, LOW);
      val1 = 0;
      delay(dt);
    }
  }


  if (results.value == 0x1FED827)
  {
    val2 = digitalRead(Relay2);
    if (val2 == 0)
    {
      digitalWrite(Relay2, HIGH);
      val2 = 1;
      delay(dt);
    }
    else
    {
      digitalWrite(Relay2, LOW);
      val2 = 0;
      delay(dt);
    }
  }


  if (results.value == 0x1FEF807)
  {
    val3 = digitalRead(Relay3);
    if (val3 == 0)
    {
      digitalWrite(Relay3, HIGH);
      val3 = 1;
      delay(dt);
    }
    else
    {
      digitalWrite(Relay3, LOW);
      val3 = 0;
      delay(dt);
    }
  }


  if (results.value == 0x1FE30CF)
  {
    val4 = digitalRead(Relay4);
    if (val4 == 0)
    {
      digitalWrite(Relay4, HIGH);
      val4 = 1;
      delay(dt);
    }
    else
    {
      digitalWrite(Relay4, LOW);
      val4 = 0;
      delay(dt);
    }
  }

  
  if (results.value == 0x1FE48B7)
  {
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
  }
  
}
