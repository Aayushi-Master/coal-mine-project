#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// ENTER YOUR WI-FI CREDENTIALS
const char* STATION_SSID = "";
const char* STATION_PASSWORD = "";

// REPLACE WITH THE RECEIVER'S IP ADDRESS (Printed on Receiver LCD/Serial)
const String RECEIVER_IP = ""; 

unsigned long lastTime = 0;
unsigned long timerDelay = 2000; // Sends data every 2 seconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(STATION_SSID, STATION_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nSender 1 Connected to Wi-Fi");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      
      int gasValue = analogRead(A0); // Read MQ-2 Sensor on A0
      String serverPath = "http://" + RECEIVER_IP + "/update";
      
      http.begin(client, serverPath);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      // CRITICAL DIFFERENCE: Sender 1 sends id=1
      String httpRequestData = "id=1&val=" + String(gasValue);
      
      int httpResponseCode = http.POST(httpRequestData);
      
      Serial.print("Sent Gas 1: ");
      Serial.print(gasValue);
      Serial.print(" | Response code: ");
      Serial.println(httpResponseCode);
      
      http.end();
    }
    lastTime = millis();
  }
}
