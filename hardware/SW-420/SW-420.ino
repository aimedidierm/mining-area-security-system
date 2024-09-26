#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

const int sensorPin = 25;

void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  pinMode(sensorPin, INPUT);  // Set the sensorPin as an input pin
}

void loop() {
  if (digitalRead(sensorPin)) {               // Check if there is any vibration detected by the sensor
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected vibration...");  // Print "Detected vibration..." if vibration detected
  } 
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("...");  // Print "..." other wise
  }

  // Add a delay to avoid flooding the serial monitor
  delay(400);
}