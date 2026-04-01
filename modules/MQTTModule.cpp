#include "FreeRTOS.h"
#include "inc/MQTTModule.h"
// #include "../inc/rc_config.h"



MQTTModule::MQTTModule(){}
MQTTModule::MQTTModule(std::string host_ip, QOS defaultQOS, std::string client_id):defaultQOS(defaultQOS), client_id(client_id) {
    
    this->good_host_ip = ip4addr_aton(host_ip.c_str(), &this->host_ip);

}


MQTTModule::~MQTTModule() {
    
}

int MQTTModule::mqtt_connect() {

    return helper_connect(this->client_id.c_str());

}

int MQTTModule::init() {

    return mqtt_init(this->host_ip, this->client_id.c_str(),this,&MQTTModule::enqueue);

}

void MQTTModule::mqtt_disconnect() {

    helper_disconnect();

}

message_buf MQTTModule::dequeue() {

    message_buf m = msgqueue.front();
    msgqueue.pop();
    return m;

}
    
int MQTTModule::publish(std::string topic, char * payload) {
    printf("trying publish!\n");
    return helper_publish(( char*)topic.c_str(),payload,this->defaultQOS);

}

