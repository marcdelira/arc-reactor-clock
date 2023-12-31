#include "DateTimeDisplay.h"

#define CLK 14
#define DIO 12
#define WAIT_CLOCK 1000
#define WAIT_COLON 500

long timeOffset = -10800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, timeOffset);

TM1637Display display(CLK, DIO);

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D

const uint8_t SEG_ERRO[] = {
	SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,           // E
	SEG_E | SEG_G,                                   // r
	SEG_E | SEG_G,                                   // r
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F    // O
	};

const uint8_t SEG_INIT[] = {
	SEG_G,   // -
	SEG_G,   // -
	SEG_G,   // -
	SEG_G    // -
	};

void display_cuckoo() {

  for (int i = 0; i < 88; i+=2) {
    display.showNumberDecEx(i, 0b01000000, true, 2, 0);
    display.showNumberDecEx(i, 0b00000000, true, 2, 2);
  }

  display.showNumberDecEx(88, 0b01000000, true, 2, 0);
  display.showNumberDecEx(88, 0b00000000, true, 2, 2);
  // flash_cuckoo();
  //delay(2000);
}

void initDateTime() {
  //Serial.begin(115200);
  display.clear();
  display.setBrightness(2);
  display.setSegments(SEG_INIT);
  delay(50);
}

void showDateTime() {
  
  while ( WiFi.status() != WL_CONNECTED ) {
    display.setSegments(SEG_ERRO);
  }

  timeClient.begin();
}

void atualizaHora() {
  int hour, minute;
  uint8_t colon = 0b01000000;

  timeClient.update();

  hour = timeClient.getHours();
  minute = timeClient.getMinutes();

  display.showNumberDecEx(hour, colon, true, 2, 0);
  display.showNumberDecEx(minute, 0b00000000, true, 2, 2);
}

void animate() {
  display_cuckoo();
  atualizaHora();
  rainbow5(12);
  efeitoStart(true);
}

void handleDateTimeDisplay() {
  static long dtInstant = 0;
  static char tmFlag = 1;

  if (millis() - dtInstant >= WAIT_CLOCK || dtInstant == 0) {
    atualizaHora();    
    dtInstant = millis();

    // lógica de controle para habilitar a animação de hora em hora...
    if (!timeClient.getMinutes() == 0) {
      tmFlag = 1;
    }

    // executar animação a cada virada de hora...
    if (timeClient.getMinutes() == 0 && tmFlag == 1) {
      tmFlag = 0;
      animate();
    } 
  }
}