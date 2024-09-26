#include <LiquidCrystal_I2C.h>

const int lcdColumns = 16;
const int lcdRows = 2;
const int redLed = 26;
const int greenLed = 33;
const int buzzer = 32;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

void setup() {
  lcd.init();
  lcd.backlight();
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzer, LOW);

  lcd.setCursor(0, 0);
  lcd.print("IoT based Mining");
  lcd.setCursor(0, 1);
  lcd.print("Security System");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(3000);
}

void loop() {
  // digitalWrite(redLed, HIGH);
  // digitalWrite(greenLed, HIGH);
  // digitalWrite(buzzer, HIGH);
  // delay(1000);
  // digitalWrite(redLed, LOW);
  // digitalWrite(greenLed, LOW);
  // digitalWrite(buzzer, LOW);
  // delay(1000);
}