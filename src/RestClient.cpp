#include "../include/RestClient.hpp"
#include <ArduinoJson.h>

RestClient::RestClient()
{
    this->httpClient = new HTTPClient();
}

DynamicJsonDocument RestClient::get(String url, DynamicJsonDocument headers)
{
    this->httpClient->begin(url);

    for (JsonPair header : headers.as<JsonObject>())
    {
        this->httpClient->addHeader(header.key().c_str(), header.value().as<char *>());
    }
    int response = this->httpClient->GET();

    DynamicJsonDocument output(1024);
    if (response <= 1)
    {
        handleError(response);
        this->httpClient->end();
        return output;
    }
    else
    {
        handleSuccessfulResponse(response);
        deserializeJson(output, this->httpClient->getString());
        this->httpClient->end();
        return output;
    }
}

DynamicJsonDocument RestClient::post(String url, DynamicJsonDocument payload)
{
    this->httpClient->begin(url);
    this->httpClient->addHeader("Content-Type", "application/json");

    String serializedPayload;
    serializeJson(payload, serializedPayload);
    int response = this->httpClient->POST(serializedPayload);

    DynamicJsonDocument output(1024);
    if (response <= 1)
    {
        handleError(response);
        this->httpClient->end();
        return output;
    }
    else
    {
        handleSuccessfulResponse(response);
        deserializeJson(output, this->httpClient->getString());
        this->httpClient->end();
        return output;
    }
}

void RestClient::put(String url, DynamicJsonDocument payload)
{
    this->httpClient->begin(url);
    this->httpClient->addHeader("Content-Type", "application/json");

    String serializedPayload;
    serializeJson(payload, serializedPayload);
    int response = this->httpClient->PUT(serializedPayload);

    if (response <= 1)
    {
        handleError(response);
        this->httpClient->end();
    }
    else
    {
        handleSuccessfulResponse(response);
        this->httpClient->end();
    }
}

void RestClient::handleError(int response)
{
    Serial.print("Error Code: ");
    Serial.println(response);
}

void RestClient::handleSuccessfulResponse(int response)
{
    Serial.print("Response Code: ");
    Serial.println(response);
}

RestClient::~RestClient()
{
    delete this->httpClient;
}