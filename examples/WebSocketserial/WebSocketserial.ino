/*
MIT License

Copyright (c) 2020 kmwebnet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include <Arduino.h>
#include <WiFi.h>
#include <rainbowtype.h>
#include <WebSocketsClient_Generic.h>
#include <HardwareSerial.h>

HardwareSerial ser(2);

char CLIENT_ID[18];

char wifissid[32];
char wifipass[64];

const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \

"-----END CERTIFICATE-----\n";

WebSocketsClient webSocket;

char serbuf[8000];
char wsbuf[2000];
size_t serbuflen = 0;
size_t wsbuflen = 0;

portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\r\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\r\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected");
      break;
      
    case WStype_TEXT:
      if (length == 0) break;
      payload[length] = 0;
       taskENTER_CRITICAL_ISR(&myMutex);
        memcpy(&wsbuf[wsbuflen], payload, length);
        wsbuflen += length; 
       taskEXIT_CRITICAL_ISR(&myMutex);
      break;
    case WStype_BIN:
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;

    default:
      break;  
  }
}

void serialtask(void* param) {
  ser.begin(115200, SERIAL_8N1, 18, 19 );  
  while (!ser);
  Serial.println("serial init..\r\n");
  while (1)
  {
   int len = ser.available();
   if (len > 0) {
    taskENTER_CRITICAL_ISR(&myMutex);
    for (int i=0; i < len; i++){
      serbuf[serbuflen] = ser.read();
      serbuflen ++;
    }
    serbuf[serbuflen] = 0;
    taskEXIT_CRITICAL_ISR(&myMutex);

   }
   if (wsbuflen > 0){
     ser.write((const uint8_t *)wsbuf, wsbuflen);
     wsbuflen = 0;   
   }
     delay(1) ;
     
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart ESP32_WebSocketClientSSL on " + String(ARDUINO_BOARD));
  
  getid(CLIENT_ID);
  wifiinit(wifissid, wifipass);

  WiFi.begin(wifissid, wifipass);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("Connected.\r\n");


  xTaskCreatePinnedToCore(serialtask, "Task0", 4096, NULL, 1, NULL, 0);

  webSocket.beginSslWithCA(<URL>, 5000, "/ws", root_ca);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // put your main code here, to run repeatedly:

  // waiting for recieving data
  webSocket.loop();
  if (serbuflen > 0) {
    webSocket.sendBIN((const uint8_t *)serbuf, serbuflen);
    serbuflen = 0;
  }
    delay(1) ;

}