#include "Module.h"
#include "lwip/ip_addr.h"
#include <iostream>

class WiFiModule : public Module {

    ip_addr_t ip;
    std::string ssid = "";
    std::string pass = "";
    int32_t rssi = 0;

    public:


        WiFiModule(std::string ssid, std::string pass);
        WiFiModule();
        ~WiFiModule();


        int getRSSI() const;
        uint32_t getIP() const;

        int initWiFi();
        int stopWiFi();


        int connect() {
            return this->initWiFi()==Module::OK;
        }

    
        virtual bool enable() {

            
            this->setEnabled(true);
            return this->isEnabled();

        }

        virtual bool disable() {

            return stopWiFi();

        }

        virtual void update(){}
        


};