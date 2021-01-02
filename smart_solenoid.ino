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
#include "memory.h"
#include "wifimanager_adapter.h"
#include "solenoid_server.h"

SolenoidServer solenoid_server(80);
Configuration config;
Memory memory;

void setup()
{
    Serial.begin(115200);

    init_config();
    delay(500);

    pinMode(config.output_pin, OUTPUT);
    delay(500);

    setup_wifi();
    delay(500);
}

void loop()
{
    solenoid_server.Listen(config);
}

void init_config()
{
    WifiManagerAdapter wm;

    //Load Config
    config = memory.Load();

    //TODO: Use an input to trigger the portal and
    // default to starting up from saved data
    //For now, always run the wm portal
    wm.setup(&config);

    //Save
    memory.Save(config);
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