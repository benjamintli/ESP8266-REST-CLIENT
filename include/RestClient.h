#ifndef REST_CLIENT
#define REST_CLIENT

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

class RestClient
{
public:
    RestClient();
    DynamicJsonDocument get(String url, JsonObject headers);
    DynamicJsonDocument post(String url, DynamicJsonDocument payload);
    void put(String url, JsonDocument payload);
    void del(String url, JsonDocument payload);
    ~RestClient();
private:
    HTTPClient* httpClient;
};

#endif