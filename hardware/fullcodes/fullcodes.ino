#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Wi-Fi credentials
const char* ssid = "Balance";       // Replace with your Wi-Fi SSID
const char* password = "balance1234"; // Replace with your Wi-Fi password

// Endpoint URL
const char* serverName = "https://0755-197-157-187-54.ngrok-free.app/api/hardware";

// Sensor and other GPIO configurations
const int timeSeconds = 3;
const int DHT11PIN = 23;
const int lcdColumns = 16;
const int lcdRows = 2;
const int redLed = 26;
const int greenLed = 33;
const int buzzer = 32;
const int vibrationSensor = 25;
const int motionSensor = 27;
const int humiHigher = 60;

char incidentMessage[] = "Sample";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
DHT dht(DHT11PIN, DHT11);

unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Wi-Fi setup
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected.");
}

// HTTP POST request function using WiFiClientSecure
void sendIncidentToServer(String incidentType, float temperature, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // Disable SSL certificate validation
    
    HTTPClient http;
    http.begin(client, serverName); // Connect to the server using insecure client
    http.addHeader("Content-Type", "application/json"); // Set the content type

    // Create JSON payload
    String jsonPayload = "{";
    jsonPayload += "\"incident\": \"" + incidentType + "\",";
    jsonPayload += "\"temperature\": " + String(temperature) + ",";
    jsonPayload += "\"humidity\": " + String(humidity);
    jsonPayload += "}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response payload
      Serial.println(httpResponseCode);   // Print the response code
      Serial.println(response);           // Print the response message
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Close connection
  } else {
    Serial.println("Wi-Fi not connected");
  }
}

// PIR sensor interrupt handler
void IRAM_ATTR detectsMovement() {
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  // Initialize peripherals
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);

  // Configure pins
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(vibrationSensor, INPUT);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  // Set initial states for LEDs and buzzer
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzer, LOW);

  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("IoT based Mining");
  lcd.setCursor(0, 1);
  lcd.print("Security System");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(3000);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  now = millis();
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if (digitalRead(vibrationSensor) && humi > humiHigher) {
    strcpy(incidentMessage, "Vib & Humidity");
    if (startTimer && !motion) {
      motion = true;
      incidentWithMotion(temp, humi);
    } else {
      incidentWithoutMotion(temp, humi);
    }
  } else if (digitalRead(vibrationSensor)) {
    strcpy(incidentMessage, "Vibration");
    if (startTimer && !motion) {
      motion = true;
      incidentWithMotion(temp, humi);
    } else {
      incidentWithoutMotion(temp, humi);
    }
  } else if (humi > humiHigher) {
    strcpy(incidentMessage, "Humidity");
    if (startTimer && !motion) {
      motion = true;
      incidentWithMotion(temp, humi);
    } else {
      incidentWithoutMotion(temp, humi);
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome here!");
    lcd.setCursor(0, 1);
    lcd.print((String)temp + "C");
    digitalWrite(greenLed, HIGH);
    motion = false;
    delay(400);
  }

  // Print sensor readings to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
}

void incidentWithoutMotion(float temp, float humi) {
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

  // Send incident details to the server
  sendIncidentToServer(incidentMessage, temp, humi);
}

void incidentWithMotion(float temp, float humi) {
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

  // Send incident details to the server
  sendIncidentToServer(incidentMessage, temp, humi);
}
