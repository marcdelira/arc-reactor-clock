#ifndef NETCONFIG_H
  #define NETCONFIG_H

  //#include <ESP8266WebServer.h>
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  //#include <DNSServer.h>
  #include <WiFiManager.h>

  void initNetworkService();
  void webServerHandleClient();
  void resetNetworkConfig();

#endif //NETCONFIG_H