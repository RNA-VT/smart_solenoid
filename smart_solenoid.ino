#include <Esp.h>

#ifdef ESP8266
#include <esp8266wifi.h>
#include <ESP8266WebServer.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <ArduinoJson.h>
#include <EEPROM.h>

#include "config.h"
#include "wifimanager_adapter.h"

Configuration config;

void setup()
{
    Serial.begin(115200);
    WifiManagerAdapter wm;

    //Load Config
    EEPROM.begin(512);
    EEPROM.get(0, config);

    //TODO: Use an input to trigger the portal and
    // default to starting up from saved data
    //For now, always run the wm portal
    wm.setup(&config);

    //Save
    EEPROM.put(0, config);
    if (EEPROM.commit())
    {
        Serial.println("Settings saved");
    }
    else
    {
        Serial.println("EEPROM error");
    }
    delay(500);
    pinMode(config.output_pin, OUTPUT);

    setup_wifi();
    delay(500);
}

void loop()
{
}

void setup_wifi()
{
    WiFi.begin();
    WiFi.setSleep(false);

    IPAddress ip(config.ip);
    IPAddress gateway(config.gateway);
    IPAddress subnet(config.subnet);
    WiFi.config(ip, gateway, subnet);

    int loop_limit = 30;
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < loop_limit)
    {
        Serial.println("-~~<*}(~){*>~~-\n");
        delay(500);
        count++;
    }
    if (count == loop_limit)
    {
        ESP.restart();
    }
    Serial.println("WiFi connected, IP = ");
    Serial.println(WiFi.localIP());
    delay(500);
}