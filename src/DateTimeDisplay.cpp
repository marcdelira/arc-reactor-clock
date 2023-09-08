#include "DateTimeDisplay.h"

#define CLK 14
#define DIO 12
#define WAIT_CLOCK 1000
#define WAIT_COLON 500

long timeOffset = -10800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, timeOffset);

TM1637Display display(CLK, DIO);

const uint8_t SEG_ERRO[] = {
	SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,           // E
	SEG_E | SEG_G,                                   // r
	SEG_E | SEG_G,                                   // r
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F    // O
	};

void initDateTime() {
  Serial.begin(115200);

  while ( WiFi.status() != WL_CONNECTED ) {
    display.setSegments(SEG_ERRO);
  }

  timeClient.begin();
  display.setBrightness(2);
}


void handleDateTimeDisplay() {
  static long dtInstant = 0;
  int hour, minute;
  uint8_t colon = 0b01000000;
  // static bool showColon = false;

  if (millis() - dtInstant >= WAIT_CLOCK || dtInstant == 0) {
    // showColon = !showColon;
    // colon = (showColon? 0b01000000 : 0b00000000);
    
    timeClient.update();
    hour = timeClient.getHours();
    minute = timeClient.getMinutes();

    display.showNumberDecEx(hour, colon, true, 2, 0);
    display.showNumberDecEx(minute, colon, true, 2, 2);
    
    dtInstant = millis();
    // Serial.println(timeClient.getFormattedTime()); 
  }
}