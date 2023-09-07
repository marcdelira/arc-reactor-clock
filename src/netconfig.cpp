#include "netconfig.h"


void initNetworkService() {

  WiFiManager wifiManager;
  wifiManager.setConfigPortalTimeout(240);

  // Cria um access point chamado "nome da rede" e senha "senha"
  if (!wifiManager.autoConnect("ESP_ARDUINOECIA", "arduinoecia")) {
    Serial.println(F("Falha na conexão. Resetar e tentar novamente..."));
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  // mensagem em caso de conexão bem sucedida
  Serial.print(F("Conectando na rede Wifi: "));
  Serial.println(WiFi.SSID());
  Serial.print(F("Endereço IP: "));
  Serial.println(WiFi.localIP());
}


void webServerHandleClient() {}

 void resetNetworkConfig() {
   WiFiManager wifiManager;

   Serial.println(F("Resetando as configurações de rede"));

   // apagar as configurações de conexão na rede Wifi
   wifiManager.resetSettings();
   // Apagar no ESP as configurações de rede Wifi salvas
   ESP.eraseConfig();
   Serial.println(F("Configurações resetadas"));
   // Reiniciar o ESP
   ESP.reset();
 }