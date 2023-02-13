//This is Second Version of the remote.
//In this I am using
// 1) Simple on and off switch feature.
// 2) One Power button switch to off all but one switch
// 3) LCD Screen to print the status of Button
// 4) Phototransistors to automate light to turn it on automatically
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;

// Initializing the pins for Relay
int Relay1 = 7;
int Relay2 = 8;
int Relay3 = 9;
int Relay4 = 10;

// Inializing the variable for storing the last status of Relay_pins
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

//Delay time for various purpose
int dt = 60;
int dt2 = 100; //Delay time to receive the signal
int dt1 = 1000; //Delay time for LCD to print next code
int dt3 = 3500; //Delay time for LCD
int dt4 = 5000; //Good Night Msg

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Setup of Photoresistor
int lightpen=A0;
int lightval;
int greenled=3;

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

  //LCD Setup
  lcd.begin();// Start the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I am online");
  lcd.setCursor(0, 1);
  lcd.print("Press any button");
  delay(dt3);
  
  //Photoresistor Setup
  pinMode(lightpen,INPUT);
  pinMode(greenled,OUTPUT);
}


void loop()

{
      //Codes for photoresistor
lightval=analogRead(lightpen);
Serial.println(lightval);
delay(200);
if(lightval<270)
{
  digitalWrite(greenled,HIGH);
}
else
{
  digitalWrite(greenled,LOW);
}
  while (irrecv.decode(&results) == 0) {}
  Serial.println(results.value, HEX);
  delay(dt2);
  irrecv.resume();
   
    if (irrecv.decode(&results))
    {
      Serial.println(results.value, HEX); // Print the Serial 'results.value'
      irrecv.resume();   // Receive the next value
      delay(dt2);
    }
  if (results.value == 0x14EB58A7)
  {
    val1 = digitalRead(Relay1);
    if (val1 == 0)
    {
      digitalWrite(Relay1, HIGH);
      val1 = 1;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 1");
      lcd.setCursor(0, 1);
      lcd.print("Light is OFF now");
      delay(dt3);

    }
    else
    {
      digitalWrite(Relay1, LOW);
      val1 = 0;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 1");
      lcd.setCursor(0, 1);
      lcd.print("Light is ON");
      delay(dt3);
    }
  }


  if (results.value == 0x14EB8877)
  {
    val2 = digitalRead(Relay2);
    if (val2 == 0)
    {
      digitalWrite(Relay2, HIGH);
      val2 = 1;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 2");
      lcd.setCursor(0, 1);
      lcd.print("TV is OFF now");
      delay(dt3);
    }
    else
    {
      digitalWrite(Relay2, LOW);
      val2 = 0;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 2");
      lcd.setCursor(0, 1);
      lcd.print("TV is ON");
      delay(dt3);

    }
  }


  if (results.value == 0x14EB906F)
  {
    val3 = digitalRead(Relay3);
    if (val3 == 0)
    {
      digitalWrite(Relay3, HIGH);
      val3 = 1;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 3");
      lcd.setCursor(0, 1);
      lcd.print("Bulb is OFF now");
      delay(dt3);
    }
    else
    {
      digitalWrite(Relay3, LOW);
      val3 = 0;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 3");
      lcd.setCursor(0, 1);
      lcd.print("BULB is ON");
      delay(dt3);
    }
  }


  if (results.value == 0x14EBD827)
  {
    val4 = digitalRead(Relay4);
    if (val4 == 0)
    {
      digitalWrite(Relay4, HIGH);
      val4 = 1;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 4");
      lcd.setCursor(0, 1);
      lcd.print("FAN is OFF now");
      delay(dt3);
    }
    else
    {
      digitalWrite(Relay4, LOW);
      val4 = 0;
      delay(dt);
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("You pressed 4");
      lcd.setCursor(0, 1);
      lcd.print("FAN is ON");
      delay(dt3);
    }
  }


  if (results.value == 0x14EB18E7)
  {
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
    lcd.clear(); //LCD Code to print status
    lcd.setCursor(0, 0);
    lcd.print("You pressed PWR");
    lcd.setCursor(0,1);
    lcd.print("All Devices off");
    delay(dt4);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Good Night...!!");
    delay(dt4);
  }

  if (results.value == 0x14EB18E7)
  {
    lcd.clear();
  }
  else
  {
    lcd.clear(); //LCD Code to print status
    lcd.setCursor(0, 0);
    lcd.print("Press OK to Know");
    lcd.setCursor(0, 1);
    lcd.print("the status ");
    delay(dt3);
    //lcd.setCursor(0, 0);
    //lcd.print("Press zero to Know");
    //lcd.setCursor(0, 1);
    //lcd.print("the status of Light");
    //delay(dt3);
  }


  //These are the codes to print the stauts of the Devices
  if (results.value == 0x14EBE01F) //Button to know the Status of Devices
  {
    //Status of Light
    if (val1 == 0)
    {
      lcd.clear(); //LCD Code to print status
      lcd.setCursor(0, 0);
      lcd.print("Light ON,");
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Light OFF,");
    }

    // Status of TV
    if (val2 == 0)
    {
       //LCD Code to print status
      lcd.setCursor(10, 0);
      lcd.print("TV ON");
    }
    else
    {
      lcd.setCursor(10, 0);
      lcd.print("TV OFF");
      
    }
    
    // Status of Bulb
    if (val3 == 0)
    {
      //LCD Code to print status
      lcd.setCursor(0, 1);
      lcd.print("BULB ON,");
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("BULB OFF,");
    }
    
    //Status of Fan
    if (val4 == 0)
    {
      //LCD Code to print status
      lcd.setCursor(10, 1);
      lcd.print("FAN ON");
      
    }
    else
    {
      lcd.setCursor(9, 1);
      lcd.print("FAN OFF");
    
    }
  }//Closing of Status of Devices
     
     

  } //Last Braces of the end of loop
