#include "voicecontrol.h"
#include "ledring.h"

Espalexa personalAssistant;


//void colorLightChanged(uint8_t brilho, uint32_t rgb) {
void colorLightChanged(EspalexaDevice *d) {
  //do what you need to do here, for example control RGB LED strip
  Serial.print("Brightness: ");
  Serial.print(d->getValue());
  Serial.print(", Red: ");
  Serial.print(d->getR()); //get red component
  Serial.print(", Green: ");
  Serial.print(d->getG()); //get green
  Serial.print(", Blue: ");
  Serial.println(d->getB()); //get blue
  
  ajustarBrilhoCor(d->getValue(), d->getRGB());
}

void handleVoiceControl() {
  personalAssistant.loop();
}

void initVoiceControl() {
  personalAssistant.addDevice("Luminária", colorLightChanged, EspalexaDeviceType::color);
  personalAssistant.begin();
}