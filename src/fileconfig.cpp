#include "fileconfig.h"

void initFileConfig() {

  if (!LittleFS.begin()) {
    Serial.println("Ocorreu um erro durante a montagem do LittleFS");
    return;
  }

  File f = LittleFS.open("/cfg/factory.txt", "r");
  if (!f) {
    Serial.println("Falha na abertura do arquivo para leitura");
    return;
  }

  Serial.println("Conteudo do arquivo: ");
  while (f.available()) {
    Serial.write(f.read());
  }
  f.close();
}