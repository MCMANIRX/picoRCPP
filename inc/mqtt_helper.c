#include "mqtt_helper.h"


err_t err;
ip_addr_t ip;
mqtt_client_t *client;
struct mqtt_connect_client_info_t ci;


char _id[64];  //MQTT client id for reconnect
void (*_ext_callback)(void*, struct message_buf* ); //ptr for callback fcn for MQTTModule
void *ctx = NULL; // MQTTModule ptr


struct message_buf mbuf;


