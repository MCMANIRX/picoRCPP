#include "FreeRTOS.h"
#include "task.h"


#include "inc/WiFiModule.h"
#include "pico/cyw43_arch.h"
#include "lwip/ip_addr.h"
#include "lwip/dns.h"

#include <iostream>     

int WiFiModule::getRSSI() const {
    
    if(!this->isEnabled())return 0xff;
    cyw43_ioctl(&cyw43_state, 254, sizeof rssi, (uint8_t *)&rssi, CYW43_ITF_STA);
    return rssi;

}

uint32_t WiFiModule::getIP() const {

    return ip.addr;
}

int WiFiModule::initWiFi()
{

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_USA))
    {
       printf("failed to initialise\n");
        return 1;
    }
    printf("initialised\n");

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(ssid.c_str(), pass.c_str(), CYW43_AUTH_WPA2_AES_PSK, 10000))
    {
        printf("failed to connect\n");

        if(cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
            initWiFi();
    }

    if (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
    {
        printf("tcp not connected, status = %d\n", cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA));
        vTaskDelay(500);
        initWiFi();
    }

   // printf("connected to Wi-Fi\n");
    ip_addr_t ip = cyw43_state.netif[0].ip_addr;

    // Following strings are the components of ifcongig[]
    printf("connected as %s\n", ip4addr_ntoa(&ip));
    printf("subnetmask: %s\n", ip4addr_ntoa(&cyw43_state.netif[0].netmask));
    printf("gateway: %s\n", ip4addr_ntoa((ip_addr_t *)&cyw43_state.netif[0].gw.addr));
    printf("DNS: %s\n", ip4addr_ntoa(dns_getserver(0)));

    this->getRSSI();
    printf("RSSI: %d\n",rssi);

    

    return 0;
}

WiFiModule::~WiFiModule(){}


int WiFiModule::stopWiFi(){
    
    cyw43_arch_lwip_end();
    cyw43_deinit(&cyw43_state);

}

 WiFiModule::WiFiModule(std::string ssid, std::string pass):ssid(ssid),pass(pass){}
