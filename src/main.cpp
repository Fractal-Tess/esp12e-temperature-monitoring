#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <wifi.hpp>

DHT_Unified dht(0, DHT11);
const String ENDPOINT = "http://192.168.0.3:9980/temperature";

void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  initWiFi();
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
}

void showErr()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;

    sensors_event_t dht_event;
    StaticJsonDocument<200> data;

    dht.temperature().getEvent(&dht_event);
    data["temperature"] = dht_event.temperature;

    dht.humidity().getEvent(&dht_event);
    data["humidity"] = dht_event.relative_humidity;

    http.begin(client, ENDPOINT.c_str());
    http.addHeader("content-type", "application/json");

    String dataString;
    serializeJson(data, dataString);

    int code = http.POST(dataString);
    if (code != 200)
    {
      Serial.println(code);
      showErr();
    }
  }
  else
  {
    showErr();
  }
  delay(1000);
}
