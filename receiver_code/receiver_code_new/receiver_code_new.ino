#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ThingSpeak.h> 
#define BUZZER D5
// ENTER YOUR WI-FI CREDENTIALS
const char* STATION_SSID = "";
const char* STATION_PASSWORD = "";

// ENTER YOUR THINGSPEAK DETAILS
unsigned long myChannelNumber = ;      // Replace with your Channel ID
const char * myWriteAPIKey = ""; // Replace with your Write API Key

WiFiClient client;
ESP8266WebServer server(80);

// Initialize LCD (Address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define LED Pins
const int GREEN_LED = D4;
const int YELLOW_LED = D3;
const int RED_LED = D0;

// Threshold values for MQ-2 (Change these to fit your environmental calibration)
const int THRESHOLD_WARNING = 300; 
const int THRESHOLD_DANGER = 500;  

// Variables to store gas data
int gas1 = 0;
int gas2 = 0;
unsigned long lastBlinkTime = 0;
bool greenState = LOW;

// Timing variable for ThingSpeak updates (runs every 20 seconds)
unsigned long lastThingSpeakUpdate = 0;
const unsigned long thingSpeakInterval = 20000; 

// Function to handle HTTP POST updates from senders
void handleData() {
  if (server.hasArg("plain") == false) {
    server.send(400, "text/plain", "Body not received");
    return;
  }
  
  String rawData = server.arg("plain");
  int idIndex = rawData.indexOf("id=");
  int valIndex = rawData.indexOf("&val=");
  
  if (idIndex != -1 && valIndex != -1) {
    int id = rawData.substring(idIndex + 3, valIndex).toInt();
    int val = rawData.substring(valIndex + 5).toInt();
    
    if (id == 1) gas1 = val;
    if (id == 2) gas2 = val;
    
    server.send(200, "text/plain", "Data Received");
  } else {
    server.send(400, "text/plain", "Bad Request Format");
  }
}
void setup() {
  Serial.begin(115200);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting Wi-Fi");

  WiFi.begin(STATION_SSID, STATION_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nReceiver Connected!");
  Serial.print("Receiver IP Address: ");
  Serial.println(WiFi.localIP()); 
  
  // Flash IP Address to the screen on boot so you can update Senders easily
  lcd.clear();
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
  delay(3000); 
  
  server.on("/update", HTTP_POST, handleData);
  server.begin();

  ThingSpeak.begin(client); 
}

void loop() {
  server.handleClient();

  // Row 1: Print Gas 1 and Gas 2 levels
  lcd.setCursor(0, 0);
  lcd.print("G1: ");
  lcd.print(gas1);
  lcd.print("   "); // Trailing spaces clear old characters
  
  lcd.setCursor(8, 0);
  lcd.print("G2: ");
  lcd.print(gas2);
  lcd.print("   ");

  // Row 2: Condition Alerts and Lights Logic
  lcd.setCursor(0, 1);
  
  if (gas1 >= THRESHOLD_DANGER || gas2 >= THRESHOLD_DANGER) {
    lcd.print("STATUS: DANGER  ");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH); // Buzzer ON
    delay(1000);
    digitalWrite(BUZZER, LOW);  // Buzzer OFF
    delay(1000);
  } 
  else if (gas1 >= THRESHOLD_WARNING || gas2 >= THRESHOLD_WARNING) {
    lcd.print("STATUS: WARNING ");
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } 
  else {
    lcd.print("STATUS: NORMAL  ");
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    
    // Non-blocking green blink execution loop
    if (millis() - lastBlinkTime >= 500) {
      lastBlinkTime = millis();
      greenState = !greenState;
      digitalWrite(GREEN_LED, greenState);
    }
  }

  // Handle ThingSpeak Cloud uploads without blocking local sensor readings
  if (millis() - lastThingSpeakUpdate >= thingSpeakInterval) {
    if(WiFi.status() == WL_CONNECTED) {
      ThingSpeak.setField(1, gas1);
      ThingSpeak.setField(2, gas2);
      
      int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      
      if(responseCode == 200){
        Serial.println("ThingSpeak update successful.");
      } else {
        Serial.print("ThingSpeak error code: ");
        Serial.println(responseCode);
      }
    }
    lastThingSpeakUpdate = millis();
  }
}