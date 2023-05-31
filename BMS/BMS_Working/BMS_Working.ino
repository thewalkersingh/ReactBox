#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address and dimensions

// temp setup
const int temperaturePin = A7;        // Analog pin for temperature sensor
const float voltageOffset = 5.2;      // Offset voltage
const float temperatureOffset = 0.0;  // Offset temperature

// volt sensor setup
const int voltagePin = A0;  // Analog pin for voltage sensor
float adc_voltage = 0.0;    // Floats for ADC voltage & Input voltage
float voltage = 0.0;
float R1 = 30000.0;  // Floats for resistor values in divider (in ohms)
float R2 = 7500.0;
float ref_voltage = 5.0;  // Float for Reference Voltage
int adc_value = 0;        // Integer for ADC value

//led pin connection
const int redLedPin = 10;         // Pin for red LED
const int yellowLedPin = 11;      // Pin for yellow LED
const int greenLedPin = 12;       // Pin for green LED

// relay pins
const int chargingRelayPin = 9;  // Pin for charging relay
const int outputRelayPin = 8;    // Pin for output relay
const int pumpPin = 2;           // Pin for pump motor

// button pins
const int temperatureButtonPin = 6;  // Pin for temperature display button
const int voltageButtonPin = 5;      // Pin for voltage display button
const int emergencyButtonPin = 3;   // Pin for emergency button
const int outputButtonPin = 4;      // Pin for output relay button

const int temperatureThresholdHigh = 55;  // Temperature threshold for high temperature condition
const int temperatureThresholdLow = 45;   // Temperature threshold for low temperature condition
const float voltageThreshold = 12.0;      // Voltage threshold for low voltage condition

bool isEmergencyButtonPressed = false;  // Flag to indicate emergency button press
bool isOutputButtonPressed = false;     // Flag to indicate output relay button press
bool isOutputRelayManual = false;       // Flag to indicate manual control of output relay

void setup() {
  lcd.init();                         // Initialize the LCD display
  lcd.backlight();                    // Turn on the backlight
  pinMode(redLedPin, OUTPUT);         // Set red LED pin as output
  pinMode(yellowLedPin, OUTPUT);      // Set yellow LED pin as output
  pinMode(greenLedPin, OUTPUT);       // Set green LED pin as output
  pinMode(chargingRelayPin, OUTPUT);  // Set charging relay pin as output
  pinMode(outputRelayPin, OUTPUT);    // Set output relay pin as output
  pinMode(pumpPin, OUTPUT);           // Set pump motor pin as output

  pinMode(temperatureButtonPin, INPUT_PULLUP);  // Set temperature display button pin as input with pull-up resistor
  pinMode(voltageButtonPin, INPUT_PULLUP);      // Set voltage display button pin as input with pull-up resistor
  pinMode(emergencyButtonPin, INPUT_PULLUP);    // Set emergency button pin as input with pull-up resistor
  pinMode(outputButtonPin, INPUT_PULLUP);       // Set output relay button pin as input with pull-up resistor

  lcd.setCursor(0, 0);        // Move the cursor to the first line
  lcd.print("Temperature:");  // Display initial text on the first line
  lcd.setCursor(0, 1);        // Move the cursor to the second line
  lcd.print("Voltage:");      // Display initial text on the second line
}

void loop() {

  int temperature = getTemperature();   // Read the temperature
  float voltage = getBatteryVoltage();  // Read the battery voltage

  if (temperature >= temperatureThresholdHigh) {
    digitalWrite(redLedPin, HIGH);    // Turn on the red LED
    digitalWrite(yellowLedPin, LOW);  // Turn off the yellow LED
    digitalWrite(greenLedPin, LOW);   // Turn off the green LED
    if (!isOutputRelayManual) {
      digitalWrite(outputRelayPin, HIGH);  // Turn off the output relay
    }
  } else if (temperature <= temperatureThresholdLow) {
    digitalWrite(redLedPin, LOW);     // Turn off the red LED
    digitalWrite(yellowLedPin, LOW);  // Turn off the yellow LED
    digitalWrite(greenLedPin, HIGH);  // Turn on the green LED
    if (!isOutputRelayManual) {
      digitalWrite(outputRelayPin, HIGH);  // Turn off the output relay
    }
  } else {
    digitalWrite(redLedPin, LOW);      // Turn off the red LED
    digitalWrite(yellowLedPin, HIGH);  // Turn on the yellow LED
    digitalWrite(greenLedPin, LOW);    // Turn off the green LED
    if (!isOutputRelayManual) {
      digitalWrite(outputRelayPin, LOW);  // Turn on the output relay
    }
  }

  if (digitalRead(emergencyButtonPin) == LOW) {
    isEmergencyButtonPressed = true;  // Set the emergency button flag
    turnOffSystem();                  // Shut down the system
  }

  if (digitalRead(outputButtonPin) == LOW) {
    isOutputButtonPressed = true;  // Set the output relay button flag
    toggleOutputRelay();           // Toggle the state of the output relay
  }

  if (digitalRead(temperatureButtonPin) == LOW) {
    displayTemperature(temperature);  // Display the temperature on the LCD
  }

  if (digitalRead(voltageButtonPin) == LOW) {
    displayVoltage(voltage);  // Display the voltage on the LCD
  }
}

int getTemperature() {
  int temperature = analogRead(temperaturePin);  // Read the analog value
  float voltage = temperature * (5.2 / 1023.0);
  float temperatureC = -1 * ((voltage - voltageOffset) * 100 + temperatureOffset);  // Convert voltage to temperature in Celsius
  // Print the temperature to the serial monitor
  Serial.print("Temp: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  return temperatureC;
}

float getBatteryVoltage() {
  adc_value = analogRead(voltagePin);  // Read the Analog Input
  // Determine voltage at ADC input
  adc_voltage = (adc_value * ref_voltage) / 1024.0;
  // Calculate voltage at divider input
  voltage = adc_voltage / (R2 / (R1 + R2));
  // Print results to Serial Monitor to 2 decimal places
  Serial.print("Input Voltage = ");
  Serial.println(voltage, 2);
  // Short delay
  return voltage;
}

void displayTemperature(int temperature) {
  lcd.setCursor(13, 0);    // Move the cursor to the second line, 13th column
  lcd.print(temperature);  // Display the temperature
  lcd.write(0xDF);         // Display the degree symbol
  lcd.print("C  ");        // Display "C"
  delay(1000);             // Delay to avoid button bouncing
}

void displayVoltage(float voltage) {
  lcd.setCursor(9, 1);    // Move the cursor to the second line, 9th column
  lcd.print(voltage, 2);  // Display the voltage with 2 decimal places
  lcd.print("V  ");       // Display "V"
  delay(1000);            // Delay to avoid button bouncing
}

void turnOffSystem() {
  digitalWrite(pumpPin, LOW);           // Turn off the pump motor
  digitalWrite(chargingRelayPin, LOW);  // Turn off the charging relay
  digitalWrite(outputRelayPin, LOW);    // Turn off the output relay
  digitalWrite(redLedPin, LOW);         // Turn off the red LED
  digitalWrite(yellowLedPin, LOW);      // Turn off the yellow LED
  digitalWrite(greenLedPin, LOW);       // Turn off the green LED
  lcd.clear();                          // Clear the LCD display
  lcd.setCursor(0, 0);
  lcd.print("System is");
  lcd.setCursor(0, 1);
  lcd.print("shut down");
}

void toggleOutputRelay() {
  isOutputRelayManual = !isOutputRelayManual;                      // Toggle the state of the output relay manual control flag
  digitalWrite(outputRelayPin, isOutputRelayManual ? HIGH : LOW);  // Set the output relay state accordingly
}
