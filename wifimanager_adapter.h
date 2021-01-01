#ifndef WM_ADAPTER_H
#define WM_ADAPTER_H

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager/tree/development
#include "wm_params.h"
#include <EEPROM.h>

#include "config.h"

class WifiManagerAdapter {
    public:
        void setup(Configuration* config);   
};
#endif