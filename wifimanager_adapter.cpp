#include "wifimanager_adapter.h"

void WifiManagerAdapter::setup(Configuration* config)
{
    WiFiManager wm;

    config->name[23] = '\0'; //overflow defense

    WiFiManagerParameter param_name("str", "param_string", config->name, 24);
    IntParameter param_output_pin("int", "param_output_pin", config->output_pin);
    IntParameter param_inverted_output("int", "param_inverted_output", config->output_pin);

    IPAddress ip(config->ip);
    IPAddressParameter param_ip("ip", "param_ip", ip);
    IPAddress gateway(config->gateway);
    IPAddressParameter param_gateway("ip", "param_gateway", gateway);
    IPAddress subnet(config->subnet);
    IPAddressParameter param_subnet("ip", "param_subnet", subnet);

    wm.addParameter(&param_name);
    wm.addParameter(&param_output_pin);
    wm.addParameter(&param_inverted_output);
    wm.addParameter(&param_ip);
    wm.addParameter(&param_gateway);
    wm.addParameter(&param_subnet);

    //SSID & password parameters already included
    wm.startConfigPortal();

    strncpy(config->name, param_name.getValue(), 24);
    config->name[23] = '\0';
    config->output_pin = param_output_pin.getValue();
    config->inverted_output = param_inverted_output.getValue();

    if (param_ip.getValue(ip))
    {
        config->ip = ip;

        Serial.print("IP param: ");
        Serial.println(ip);
    }
    else
    {
        Serial.println("Invalid or Missing IP.");
    }

    if (param_gateway.getValue(gateway))
    {
        config->gateway = gateway;

        Serial.print("Gateway param: ");
        Serial.println(gateway);
    }
    else
    {
        Serial.println("Invalid or Missing Gateway.");
    }

    if (param_subnet.getValue(subnet))
    {
        config->subnet = subnet;

        Serial.print("Subnet param: ");
        Serial.println(subnet);
    }
    else
    {
        Serial.println("Invalid or Missing Subnet.");
    }
}