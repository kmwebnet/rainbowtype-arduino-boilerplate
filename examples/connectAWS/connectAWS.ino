#include <Arduino.h>
#include <WiFi.h>
#include "rainbowtype.h"
#include <PubSubClient.h>
#include <Arduino_JSON.h>


const char* PUB_TOPIC    = "test_topic/esp32";
const char* SUB_TOPIC    = "test_topic/esp32";
char CLIENT_ID[18];

char wifissid[32];
char wifipass[64];

const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";

WiFiClientSecure client;
PubSubClient mqttClient(client);

#define QOS 0

void connect_awsiot() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect((const char *)CLIENT_ID)) {
      Serial.println("Connected.");
      mqttClient.subscribe(SUB_TOPIC, QOS);
      Serial.println("Subscribed.");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Try again in 5 seconds");

      delay(5000);
    }
  }
}

void mqttCallback (char* topic, byte* payload, unsigned int length) {
    Serial.print("Received. topic=");
    Serial.println(topic);

    char subMessage[length];
    for (int i=0; i < length; i++) {
      subMessage[i] = (char)payload[i];
    }
    subMessage[length] = 0;
    Serial.println(subMessage);

    // parse JSON
    JSONVar obj = JSON.parse(subMessage);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  getid(CLIENT_ID);
  wifiinit(wifissid, wifipass);

  WiFi.begin(wifissid, wifipass);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("\nConnected.");

  client.setCACert(root_ca);
  client.setCertificate("dummy");
  client.setPrivateKey("dummy");
  mqttClient.setServer("XXXXXXXXXXXXX-ats.iot.us-east-1.amazonaws.com", 8883);
  mqttClient.setCallback(mqttCallback);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (!mqttClient.connected()) {
    connect_awsiot();
    mqttClient.publish( PUB_TOPIC, CLIENT_ID);
  }

  // waiting for recieving data
  mqttClient.loop();

  
  delay(5) ;

}