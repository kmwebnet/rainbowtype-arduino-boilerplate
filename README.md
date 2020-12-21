# rainbowtype-arduino-boilerplate

boilerplate for rainbowtype IoT secure prototyping system

# Requirements

Arduino IDE environment (tested 1.8.13) .

You need to setup this repo as zip at Arduino library manager.
Then, you'll find example sketches.

and you must copy "cert_chain.c" which you have generated one.

you need to modify the constants which you already have as follows:

```
mqttClient.setServer("XXXXXXXXXXXXX-ats.iot.us-east-1.amazonaws.com", 8883); on "connectAWS"

const char* root_ca = "";  on "WebSocketserial", "WebSocketcamera"
webSocket.beginSslWithCA(<URL>, 5000, "/ws", root_ca); on "WebSocketserial", "WebSocketcamera"

```

# Environment reference

Espressif ESP32-DevkitC
this project initialize both of I2C 0,1 port, and the device on I2C port 0 is absent.  
 pin assined as below:

      I2C 1 SDA GPIO_NUM_21
      I2C 1 SCL GPIO_NUM_22


Microchip ATECC608A(on I2C port 1)

you can change pin setting on Wire.begin(21 ,22); on cryptoauthlib/i2c_arduino.cpp

This code currently not supported TRUST&GO and TRUSTFLEX versions.

# Usage

Once you do download as ZIP, you need to add it as library on Arduino IDE.

# Run this project

# Result

If you run this project with success, you can find the results on serial console as follows:

```
..
   Connected.
Attempting MQTT connection...Connected.
Subscribed.

```

You can also recieve a message from "test" page on AWS IoT console

# License

This software includes open source software. These open source software are subject to the applicable license terms for each open source software. The license terms, copyright notices, and other detailed license information for such open source software can be found in each source code.
