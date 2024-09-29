#include <LiquidCrystal_I2C.h>
#include "DHT.h"

const int DHT11PIN = 23;
const int lcdColumns = 16;
const int lcdRows = 2;
const int redLed = 26;
const int greenLed = 33;
const int buzzer = 32;
const int vibrationSensor = 25;

const int humiHigher = 30;

char incidentMessage[] ="Sample";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
DHT dht(DHT11PIN, DHT11);

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(vibrationSensor, INPUT);

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
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if (digitalRead(vibrationSensor) & humi > humiHigher){
    strcpy(incidentMessage, "Vib & Humidity");
    incidentWithoutMotion();
  } else if (digitalRead(vibrationSensor)) {
    strcpy(incidentMessage, "Vibration");
    incidentWithoutMotion();
  } 
  else if(humi > humiHigher){
    strcpy(incidentMessage, "Humidity");
    incidentWithoutMotion();
  } 
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome here!");
    lcd.setCursor(0, 1);
    lcd.print((String)temp + "C");
    digitalWrite(greenLed, HIGH);
    delay(400);
  }
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
}

void incidentWithoutMotion(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(incidentMessage);
  lcd.setCursor(0, 1);
  lcd.print("Detected....");
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  delay(500);
  digitalWrite(redLed, LOW);
  delay(500);
}

void incidentWithMotion(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print(incidentMessage);
  lcd.setCursor(0, 1);
  lcd.print("Detected....");
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(redLed, LOW);
  digitalWrite(buzzer, LOW); // Turn off the buzzer after the alert
  delay(500);
}
