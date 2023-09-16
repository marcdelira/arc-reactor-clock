#include "main.h"
#include <ESP8266mDNS.h>

#define BLUE_LED1 4
#define BLUE_LED2 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel();

ESP8266WebServer server(80);

void initBlueLeds();
void startBlueLeds();

void setup(){
  Serial.begin(115200);
  
  // initNeopixel(&pixels);
  initNetworkService();
  initDateTime();

  if (!MDNS.begin("wemos")) {
    Serial.println("Erro na configuração do MDNS");
  }

  Serial.println("mDNS responder started");
  server.begin();

  MDNS.addService("http", "tcp", 80);

  server.on("/", 
    HTTP_GET,
    []() {
      server.send(200, F("text/html"),
      F("Welcome to the Rest Web Server!"));
    });
  
  Serial.println("Sending mDNS query");
  int n = MDNS.queryService("http", "tcp");  // Send out query for esp tcp services
  Serial.println("mDNS query done");
  if (n == 0) {
    Serial.println("no services found");
  } else {
    Serial.print(n);
    Serial.println(" service(s) found");
    for (int i = 0; i < n; ++i) {
      // Print details for each service found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(MDNS.hostname(i));
      Serial.print(" (");
      Serial.print(MDNS.IP(i));
      Serial.print(":");
      Serial.print(MDNS.port(i));
      Serial.println(")");
    }
  }
  Serial.println();
  initBlueLeds();
  startBlueLeds();
}

void loop() {
  MDNS.update();
  server.handleClient();
  // static long mudar = 0;

  // handleDateTimeDisplay();
  // handleLedRing();

  // if (millis() - mudar >= 5000) {
  //   //Serial.println("mudar...");
  //   mudaEfeito();
  //   mudar = millis();
  // }
}


void initBlueLeds() {
  pinMode(BLUE_LED1, OUTPUT);
  pinMode(BLUE_LED2, OUTPUT);
}

void startBlueLeds() {
  digitalWrite(BLUE_LED1, HIGH);
  digitalWrite(BLUE_LED2, HIGH);
}