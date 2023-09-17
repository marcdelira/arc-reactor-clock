#ifndef LEDRING_H
#define LEDRING_H
  
  #include <Adafruit_NeoPixel.h>

  #define PIN 5
  #define NUMPIXEL 35

  #define EFEITO_CONECTANDO 1
  #define EFEITO_HEART_BEAT 2
  #define EFEITOS_OFF -1
  //int led_i[NUMPIXEL];

  void initNeopixel(Adafruit_NeoPixel* neoPixel);
  void colorWipe(uint32_t color32, boolean isDelay);
  void testaIntensidade();
  void heartBeat();
  void efeitoConectando();
  void handleLedRing();
  void mudaEfeito();
  void rainbowCycle(uint8_t wait);
  void efeitoStart(boolean wifiConnection);
  //void pulse();


#endif //LEDRING_H