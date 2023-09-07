#ifndef DATETIMEDISPLAY_H
#define DATETIMEDISPLAY_H

#include <TM1637Display.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

void initDateTime();
void handleDateTimeDisplay();

#endif //DATETIMEDISPLAY_H