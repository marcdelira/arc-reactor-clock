#include "main.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel();

void setup(){
  initDateTime();
  initNeopixel(&pixels);
}

void loop() {
  static long mudar = 0;

  handleDateTimeDisplay();
  handleLedRing();

  if (millis() - mudar >= 5000) {
    //Serial.println("mudar...");
    mudaEfeito();
    mudar = millis();
  }
}