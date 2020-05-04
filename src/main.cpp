#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "../include/RestClient.hpp"

const char *ssid = "<ssid>";
const char *password = "<password>";

RestClient *client;

String getUrl = "http://postman-echo.com/get?fuck=1";
String postUrl = "http://postman-echo.com/post";
String putUrl = "http://postman-echo.com/put";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

DynamicJsonDocument doc(1024);

#define LED_BUILDIN 2

void httpPOSTRequest(String serverName)
{
  HTTPClient http;

  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  doc["hello"] = "world";
  String json;
  serializeJson(doc, json);

  int httpResponseCode = http.POST(json);
  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(http.getString());
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  WiFi.begin(ssid, password);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("fuck");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  client = new RestClient();
}

// the loop function runs over and over again forever
void loop()
{

  if ((millis() - lastTime) > timerDelay)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      // String response = httpGETRequest(url);
      // deserializeJson(doc, response);
      // JsonObject obj = doc.as<JsonObject>();
      // String url = obj["url"].as<String>();
      // Serial.println(url);
      //httpPOSTRequest(url);
      DynamicJsonDocument headers(1024);
      headers["Content-Type"] = "application/json";
      DynamicJsonDocument response(1024);
      response = client->get(getUrl, headers);
      String lol;
      serializeJson(response, lol);
      Serial.println(lol);
      DynamicJsonDocument payload(1024);
      payload["fuck"] = "this shit";
      response = client->post(postUrl, payload);
      client->put(putUrl, payload);

      serializeJson(response, lol);
      Serial.println(lol);
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
