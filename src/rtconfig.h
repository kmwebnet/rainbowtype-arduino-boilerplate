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
#ifndef RTCONFIG_H
#define RTCONFIG_H


#include "stdio.h"
#include "stdlib.h"

#include "cryptoauthlib/cryptoauthlib.h"

#include "cert_chain.h"

ATCAIfaceCfg cfg;
#define MAX_SSID_SIZE		32
#define MAX_PASSWORD_SIZE	64

void get_atecc608cfg(ATCAIfaceCfg *cfg);


void savemiscdata (uint8_t * data);
void restoremiscdata (uint8_t * data);

uint8_t sysinit(void);

void wifiinit(char * wifissid, char * wifipass);

void getid (char * id);

#endif