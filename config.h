#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

class Configuration
{
public:
    int output_pin;
    int inverted_output;
    char name[24];
    uint32_t ip;
    uint32_t gateway;
    uint32_t subnet;
};

#endif