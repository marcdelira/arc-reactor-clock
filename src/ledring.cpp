#include "ledring.h"

#define QTDE_EFEITOS 4

void printEfeitoSelecionado();

Adafruit_NeoPixel* ledRing;
static int efeitoSelecionado = 0;
bool habilitaEfeitoConectando = false;
bool habilitaEfeitoHeartBeat = false;

void efeitoStart(boolean wifiConnection) {
  uint32_t colorLed = 0;

  colorLed = (wifiConnection ? ledRing->Color(0, 20, 255) : ledRing->Color(255, 20, 0));

  for(int i=0; i<35;i++){
    ledRing->setPixelColor(i, colorLed);
    ledRing->show();
    delay(40);
  }
}

void initNeopixel(Adafruit_NeoPixel* neoPixel) {
  ledRing = neoPixel;
  ledRing->setPin(PIN);
  ledRing->updateLength(NUMPIXEL);
  ledRing->updateType(NEO_GRB + NEO_KHZ800);
  ledRing->begin();
  ledRing->clear();
  //ledRing->setPixelColor(0, ledRing->Color(0, 0, 150));
  ledRing->show();

  efeitoStart(false);
}

void mudaEfeito() {
  efeitoSelecionado++;
  if (efeitoSelecionado > QTDE_EFEITOS - 1) {
    efeitoSelecionado = 0;
  }
  // Serial.printf("efeitoSelecionado: %d\n", efeitoSelecionado);
}

void colorWipe(uint32_t color32, boolean isDelay) {
  for (int i = 0; i < ledRing->numPixels(); i++) {
    ledRing->setPixelColor(i, color32);
    ledRing->show();
    if (isDelay)
      delay(50); //Intervalo para a execução de cada comando para cada LED 
  }
}

void heartBeat() {
  const int batimentoMinimo = 30,
            picoAtrio       = 150,
            picoVentriculo  = 255;
  
  ledRing->clear();
  ledRing->show();
  
  // movimento átrio
  for (int i = batimentoMinimo - 20; i <= picoAtrio; i = i + 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(10);
  }

  delay(60);
  
  for (int i = picoAtrio; i >= 90; i = i - 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(20);
  }

  delay(100);

  // movimento ventrículo
  for (int i = 90; i <= picoVentriculo; i = i + 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(5);
  }

  delay(60);
  
  for (int i = picoVentriculo; i >= 15; i = i - 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(10);
  }

  delay(350);
}


void testaIntensidade() {
  int valores[] = {50, 100, 150, 200, 255, 0};
  
  for (ulong i = 0; i < (sizeof(valores) / sizeof(valores[0])); i++) {
    colorWipe(ledRing->Color(valores[i], 0, 0), true);
  }
  delay(100);

  for (ulong i = 0; i < (sizeof(valores) / sizeof(valores[0])); i++) {
    colorWipe(ledRing->Color(0, valores[i], 0), true);
  }
  delay(100);
  
  for (ulong i = 0; i < (sizeof(valores) / sizeof(valores[0])); i++) {
    colorWipe(ledRing->Color(0, 0, valores[i]), true);
  }
  delay(100);
}


void efeitoConectando() {
  uint32_t color32;
  static bool acende = true;
  static ulong timeSave = 0;
  uint espera = 20;
  static u_char index = 0;

  if (acende) {
    color32 = ledRing->Color(15, 15, 255);
   } else {
     color32 = ledRing->Color(0, 0, 0);
  }
  
  if (millis() - timeSave >= espera) {
    ledRing->setPixelColor(index, color32);
    ledRing->show();
    timeSave = millis();
    
    if (index < NUMPIXEL - 1) {
      index++;
    } else {
      acende = !acende;
      index = 0;
    }
  }

}

void desligaLedRing() {
  efeitoSelecionado = 0;
  ledRing->clear();
  ledRing->show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return ledRing->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return ledRing->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ledRing->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i;
  static uint16_t j = 0;

  j++;
  if (j >= 256) {
    j = 0;
  }

  //for(j=0; j<256*2; j++) { // 5 cycles of all colors on wheel
  for(i=0; i< ledRing->numPixels(); i++) {
    ledRing->setPixelColor(i, Wheel(((i * 256 / ledRing->numPixels()) + j) & 255));
  }
  ledRing->show();
  delay(wait);
  //}
}

void handleLedRing() {
  
  switch (efeitoSelecionado) {
    case 0:
      // desligaLedRing();
      colorWipe(ledRing->Color(0, 0, 255), true);
      colorWipe(ledRing->Color(255, 0, 0), true);
      colorWipe(ledRing->Color(0, 255, 0), true);
      break;
    case 1:
      efeitoConectando();
      break;
    case 2:
      rainbowCycle(8);
      break;
    case 3:
      heartBeat();
      break;
    default:
      efeitoSelecionado = 0;
  }
}

void printEfeitoSelecionado() {
  Serial.print("efeitoSelecionado: ");
  Serial.println(efeitoSelecionado);
}