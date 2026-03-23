#include "FreeRTOS.h"
#include "inc/MQTTModule.h"
#include "../inc/mqtt_helper.h"
// #include "../inc/rc_config.h"



MQTTModule::MQTTModule(std::string host_ip, QOS defaultQOS = QOS_0):defaultQOS(defaultQOS) {
    
    this->good_host_ip = ip4addr_aton(host_ip.c_str(), &this->host_ip);

}


MQTTModule::~MQTTModule() {
    
}

int MQTTModule::connect() {

    return helper_connect(this->client_id.c_str());

}

int MQTTModule::init() {
    return mqtt_init(this->client_id.c_str());
}

void MQTTModule::disconnect() {

    helper_disconnect();

}

