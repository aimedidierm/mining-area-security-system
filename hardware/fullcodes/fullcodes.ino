#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// WiFi credentials
const char* WIFI_SSID = "Benitha";
const char* WIFI_PASSWORD = "07/1/20_24";

// Server URL (change as needed)
const char* SERVER_URL = "http://mining.aimedidierm.xyz/api/hardware";

const int timeSeconds = 3;
const int DHT11PIN = 23;
const int lcdColumns = 16;
const int lcdRows = 2;
const int redLed = 26;
const int greenLed = 33;
const int buzzer = 32;
const int vibrationSensor = 25;
const int motionSensor = 27;
const int soilMoisturePin = 34;


const int soilMoistureThreshold = 1500;
const int humiHigher = 60;

int soilMoistureValue = 0;
int vibration = 0;

char incidentMessage[] = "Sample";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
DHT dht(DHT11PIN, DHT11);

unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

void IRAM_ATTR detectsMovement() {
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(vibrationSensor, INPUT);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(soilMoisturePin, INPUT);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzer, LOW);

  lcd.setCursor(0, 0);
  lcd.print("IoT based Mining");
  lcd.setCursor(0, 1);
  lcd.print("Security System");
  delay(4000);
  
  connectToWiFi();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(3000);
}

void loop() {
  now = millis();
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  soilMoistureValue = analogRead(soilMoisturePin);
  vibration = digitalRead(vibrationSensor);

  digitalWrite(buzzer, LOW);

  if (soilMoistureValue > soilMoistureThreshold) {
    strcpy(incidentMessage, "Soil Wet");
    handleSoilMoistureIncident(temp, humi, soilMoistureValue);
  }
  
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

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print(" Soil Moisture: ");
  Serial.print(soilMoistureValue);
  Serial.print(" Vibration: ");
  Serial.print(vibration);
  Serial.println("");
}

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  lcd.print("Connecting to WiFi");

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connected, IP:");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(2000);
  } else {
    Serial.println("\nFailed to connect to WiFi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Failed to connect");
    delay(2000);
  }
}

void sendIncidentToServer(String incidentType, float temperature, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure  client; // Use WiFiClient for HTTP requests
    client.setInsecure();
    HTTPClient http;

    String jsonPayload = "{";
    jsonPayload += "\"incident\": \"" + incidentType + "\",";
    jsonPayload += "\"temperature\": \"" + String(temperature) + "\",";
    jsonPayload += "\"moisture_level\": \"" + String(soilMoistureValue) + "\",";
    jsonPayload += "\"vibration_level\": \"" + String(vibration) + "\",";
    jsonPayload += "\"motion_level\": " + String(motion) + ",";
    jsonPayload += "\"humidity\": \"" + String(humidity);
    jsonPayload += "\"}";

    Serial.print("Sending JSON: ");
    Serial.println(jsonPayload);

    if (http.begin(client, "https://restroom.rwandahouseland.com")) {  // Pass WiFiClient and URL
      http.addHeader("Content-Type", "application/json");  // Specify content type

      int httpResponseCode = http.POST(jsonPayload);  // Send the POST request

      // Check the response code
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String response = http.getString();  // Get the response payload
        Serial.println("Response: ");
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      http.end();  // End the HTTP connection
    } else {
      Serial.println("HTTPClient failed to begin");
    }
  } else {
    Serial.println("Error: Not connected to Wi-Fi.");
  }
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

void handleSoilMoistureIncident(float temp, float humi, int soilMoisture) {
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

  // Send soil moisture incident details to the server
  sendIncidentToServer(incidentMessage, temp, humi);
}
