#include <Esp.h>

#ifdef ESP8266
#include <esp8266wifi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <ArduinoJson.h>

#define PIN 7

void setup(){
    pinMode(PIN, OUTPUT)
}

void loop(){

}

bool getState() {
    return false;
}