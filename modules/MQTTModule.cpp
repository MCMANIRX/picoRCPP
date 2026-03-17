#include "MQTTModule.h"
#include "../inc/rc_config.h"



int MQTTModule::connect(std::string client_id)
{
    client = mqtt_client_new();
    ci.client_id = id.c_str(); //"rc_unassigned";

    mqtt_client_connect(client, &ip, 1883, mqtt_connection_cb, 0, &ci);
    return subscribe(CTRL_TOPIC);
}

void MQTTModule::disconnect()
{
    unsubscribe(CTRL_TOPIC);
    mqtt_disconnect(client);
}