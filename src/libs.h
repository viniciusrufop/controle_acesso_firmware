#include <Arduino.h>
#include <WiFiManager.h>   // WiFi Configuration Magic ( https://github.com/zhouhan0126/WIFIMANAGER-ESP32 ) >> https://github.com/tzapu/WiFiManager (ORIGINAL)
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h> //biblioteca responsável pela comunicação com o módulo RFID-RC522
#include <HTTPClient.h>



// // #include <WiFi.h> //lib para configuração do Wifi
// #include <WiFiUdp.h>//Biblioteca do UDP.
// #include <NTPClient.h>//Biblioteca do NTP.
// #include <DNSServer.h> //Local DNS Server used for redirecting all requests to the configuration portal ( https://github.com/zhouhan0126/DNSServer---esp32 )
// #include <WebServer.h> //Local WebServer used to serve the configuration portal ( https://github.com/zhouhan0126/WebServer-esp32 )
// // #include <WiFiClient.h>
//

// #include <FS.h>
// #include <SPIFFS.h>
// #define FORMAT_SPIFFS_IF_FAILED true
// #include "relogio.h"
// #include "senhas.h"








// #include "lib_spiffs.h"
// #include "telas.h"
