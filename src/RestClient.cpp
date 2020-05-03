#include "../include/RestClient.h"
#include <ArduinoJson.h>

RestClient::RestClient()
{
    this->httpClient = new HTTPClient();
}


DynamicJsonDocument RestClient::get(String url, JsonObject headers)
{
    this->httpClient->begin(url);
    for( JsonPair header : headers) {
        this->httpClient->addHeader(header.key().c_str(), header.value().as<char *>());
    }
    int response = this->httpClient->GET();
    DynamicJsonDocument output(1024);
    if (response <= 1) {
        Serial.print("Error Code: ");
        Serial.println(response);
        return output;
    }
    Serial.print("Response Code: ");
    Serial.println(response);
    deserializeJson(output, this->httpClient->getString());
    this->httpClient->end();
    return output;
}

RestClient::~RestClient() 
{
    delete this->httpClient;
}