#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "../include/RestClient.h"

const char * ssid = "<enter_ssid>";
const char * password = "<enter_password>";

RestClient * client;

String url = "http://postman-echo.com/get?fuck=1";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

DynamicJsonDocument doc(1024);

#define LED_BUILDIN 2

String httpGETRequest(String serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void httpPOSTRequest(String serverName) {
  HTTPClient http;
  
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  doc["hello"] = "world";
  String json;
  serializeJson(doc, json);

  int httpResponseCode = http.POST(json);
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(http.getString());
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  WiFi.begin(ssid, password);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("fuck");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  client = new RestClient();
}

// the loop function runs over and over again forever
void loop() {

  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      // String response = httpGETRequest(url);
      // deserializeJson(doc, response);
      // JsonObject obj = doc.as<JsonObject>();
      // String url = obj["url"].as<String>();
      // Serial.println(url);
      //httpPOSTRequest(url);
      DynamicJsonDocument headers(1024);
      headers["Content-Type"] = "application/json";
      DynamicJsonDocument response(1024);
      response = client->get(url, headers.as<JsonObject>());
      String lol;
      serializeJson(response, lol);
      Serial.println(lol);
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

