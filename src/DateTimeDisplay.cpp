#include "DateTimeDisplay.h"

#define CLK 14
#define DIO 12
#define WAIT_CLOCK 1000
#define WAIT_COLON 500

const char *ssid     = "brisa-3186667";
const char *password = "btn8zqi7";

long timeOffset = -10800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, timeOffset);

TM1637Display display(CLK, DIO);

void initDateTime() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

  display.setBrightness(2);
}


void handleDateTimeDisplay() {
  static long dtInstant = 0;
  int hour, minute;
  uint8_t colon = 0b01000000;
  static bool showColon = false;

  timeClient.update();
  hour = timeClient.getHours();
  minute = timeClient.getMinutes();

  if (millis() - dtInstant >= WAIT_COLON || dtInstant == 0) {
    showColon = !showColon;

    colon = (showColon? 0b01000000 : 0b00000000);

    display.showNumberDecEx(hour, colon, true, 2, 0);
    display.showNumberDecEx(minute, colon, true, 2, 2);
    
    dtInstant = millis();
  }
    // Serial.println(timeClient.getFormattedTime()); 
}