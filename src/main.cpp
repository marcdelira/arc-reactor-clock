#include "main.h"
// #include <ESP8266mDNS.h>

#define BLUE_LED1 13
#define BLUE_LED2 15
#define BT_RESET 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel();

// ESP8266WebServer server(80);

void initBlueLeds();
void startBlueLeds();
void read_keyb();

void setup(){
  Serial.begin(115200);
  pinMode(BT_RESET, INPUT_PULLUP);
  initDateTime();
  initNeopixel(&pixels);
  
  initNetworkService();

  // if (!MDNS.begin("wemos")) {
  //   Serial.println("Erro na configuração do MDNS");
  // }

  // Serial.println("mDNS responder started");
  // server.begin();

  // MDNS.addService("http", "tcp", 80);

  // server.on("/", 
  //   HTTP_GET,
  //   []() {
  //     server.send(200, F("text/html"),
  //     F("Welcome to the Rest Web Server!"));
  //   });
  
  efeitoStart(true);
  showDateTime();
  initBlueLeds();
  startBlueLeds();
  display_cuckoo();
  initFileConfig();
  initVoiceControl();
}

void loop() {
  // MDNS.update();
  // server.handleClient();

  handleDateTimeDisplay();  
  handleVoiceControl();
  read_keyb();
}


void initBlueLeds() {
  pinMode(BLUE_LED1, OUTPUT);
  pinMode(BLUE_LED2, OUTPUT);
}

void startBlueLeds() {
  digitalWrite(BLUE_LED1, HIGH);
  digitalWrite(BLUE_LED2, HIGH);
}

void read_keyb() {
  static char flag1 = 0,
              release_bt = 0;
  static long timeInMillis = 0;

  if (digitalRead(BT_RESET)) {
    flag1 = 1;
  }

  if (!digitalRead(BT_RESET) && flag1) {
    flag1 = 0;
    release_bt = 1;
    delay(130);
    timeInMillis = millis();
  }

  if (digitalRead(BT_RESET) && release_bt) {
    release_bt = 0;
    
    if (millis() - timeInMillis >= 4900) {
      resetNetworkConfig();
    }
  }
}