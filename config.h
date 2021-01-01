#ifndef CONFIG_H
#define CONFIG_H
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager/tree/development
#include <Arduino.h>
#include "wm_params.h"
#include <EEPROM.h>

class Configuration
{
public:
    int output_pin;
    int inverted_output;
    char name[24];
    uint32_t ip;
    uint32_t gateway;
    uint32_t subnet;
    void wm_setup();
};

#endif