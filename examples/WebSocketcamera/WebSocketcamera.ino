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
#include "esp_camera.h"

char CLIENT_ID[18];

char wifissid[32];
char wifipass[64];

const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \

"-----END CERTIFICATE-----\n";

WebSocketsClient webSocket;

bool connected = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!\r\n");
      connected = false;
      break;
    case WStype_CONNECTED:
      Serial.printf("Connected to url: %s\r\n", payload);
      connected = true;
      break;
      
    case WStype_TEXT:
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
  Serial.print("Connected.\r\n");

  webSocket.beginSslWithCA(<URL>, 5000, "/ws", root_ca);
  webSocket.onEvent(webSocketEvent);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 2;
  config.pin_d1 = 5;
  config.pin_d2 = 18;
  config.pin_d3 = 19;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 32;
  config.pin_pclk = 33;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = -1;
  config.pin_reset = 14;
  config.xclk_freq_hz = 6000000; // 6000000
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA; // VGA
    config.jpeg_quality = 1; //9
    config.fb_count = 8; //8
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;

  sensor_t * s = esp_camera_sensor_get();
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

  Serial.printf("free heap size: %d\r\n", xPortGetFreeHeapSize() );
}
}



void loop() {
      webSocket.loop();

    if(connected) {
      camera_fb_t *fb = esp_camera_fb_get();
        if(!fb){
          Serial.println("Camera capture failed");
          esp_camera_fb_return(fb);
        return;
        }

      if(fb->format != PIXFORMAT_JPEG){
        Serial.println("Non-JPEG data not implemented");
        return;
      }
    // Serial.printf("fb size: %d\r\n", fb->len );
    size_t dlen = fb->len -1;
    for (int i=0; i < dlen; i++){
      if (fb->buf[i] == 0xff && fb->buf[i + 1] == 0xd9)
      {
        webSocket.sendBIN((const uint8_t *) fb->buf, i + 2);
        break;
      }
    };
          
    esp_camera_fb_return(fb);
    }

}