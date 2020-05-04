#ifndef REST_CLIENT_HPP
#define REST_CLIENT_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

class RestClient
{
public:
    RestClient();
    DynamicJsonDocument get(String url, DynamicJsonDocument headers);
    DynamicJsonDocument post(String url, DynamicJsonDocument payload);
    void put(String url, DynamicJsonDocument payload);
    ~RestClient();

private:
    void handleError(int response);
    void handleSuccessfulResponse(int response);
    HTTPClient *httpClient;
};

#endif