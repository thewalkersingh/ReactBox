#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <math.h>
 
int sensorPin = A0; // select the input pin for the potentiometer
 
double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
   //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   return Temp;
}
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.
const int redPin = A1;   //  LED pin
int motor1 = A2;
// int ThermistorPin = A0;
void setup() {
  Serial.begin(9600);
    // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  pinMode(redPin, OUTPUT);
  pinMode(motor1 , OUTPUT);
}
void loop() {
int readVal=analogRead(sensorPin);
double temp = -30.00 -(Thermistor(readVal));
 
 Serial.println(temp);  // display Temperature
  Serial.print("Temperature: "); 
  // Serial.print(temp_C);
  Serial.print(temp);
  Serial.println(" C");
   
  lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
  lcd.print("Temperature : "); // Print the temp
  lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print(temp);
  // lcd.print(" C");
  if(temp >= 50){
    analogWrite(redPin, HIGH);
    digitalWrite(motor1, HIGH);
  }else{
    analogWrite(redPin, LOW);
    digitalWrite(motor1, LOW);
  }
  delay(500);
}