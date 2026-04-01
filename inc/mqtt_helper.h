/*

QoS 0 (At most once):

This is the lowest level of service.
The message is delivered at most once, and delivery is not confirmed.
There is no guarantee that the message will be delivered, and it is possible that messages may be lost.

QoS 1 (At least once):

This level guarantees that the message will be delivered at least once to the receiver.
The sender (publisher) sends the message and expects an acknowledgment (ACK) from the receiver (subscriber).
If an ACK is not received, the sender will resend the message.
This level introduces the possibility of duplicate messages in case of network issues.

QoS 2 (Exactly once):

This is the highest level of service.
It ensures that the message is delivered exactly once to the receiver.
It involves a four-step handshake process: publish, PUBREC (publish received), PUBREL (publish release), and PUBCOMP (publish complete).
This level provides the strongest guarantee of message delivery but involves more overhead and complexity.

*/



#ifndef MQTT_H
#define MQTT_H
#include "FreeRTOS.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"

#include "pico/cyw43_arch.h"
#include "lwip/ip_addr.h"
#include "lwip/dns.h"


#include "lwip/ip_addr.h"
#include "lwip/apps/mqtt.h"
#include "rc_config.h"
 // #include "queue.h"
#include "hardware/watchdog.h"



struct message_buf {

    u8_t topic[64];
    u8_t data[256];
    u16_t len;
    bool isNewData;

};

extern ip_addr_t ip;
extern mqtt_client_t *client;
extern struct mqtt_connect_client_info_t ci;



extern char _id[64];  //MQTT client id for reconnect
extern void (*_ext_callback)(void*, struct message_buf* ); //ptr for callback fcn for MQTTModule
extern void *ctx ; // MQTTModule ptr


extern struct message_buf mbuf;






static int init_message_buf(struct message_buf * buf) {

    if(buf==NULL)return 0;

    memset(buf->data,0,sizeof(buf->data)/sizeof(uint8_t));
    memset(buf->topic,0,sizeof(buf->topic)/sizeof(uint8_t));
    buf->isNewData = false;
    buf->len = 0;

    return 1;
}



static int helper_connect(const char *id);



/// @brief 
/// @param count
/// @param delay 
static void blink(uint8_t count, int delay)
{

    for (int i = 0; i < count; ++i)
    {
        sleep_ms(delay);
        gpio_put(ULT_LED_PIN,1);
    
       // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(delay);
        gpio_put(ULT_LED_PIN,0);

       // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }
}

// #################### CALLBACKS ####################
static void pub_request_cb(void *arg, err_t result)
{
    // printf("Publish result: %d\n", result);
   // mqtt_client_t *client = (mqtt_client_t *)arg;
}

static void sub_request_cb(void *arg, err_t result)
{
    ///   printf("Subscribe result: %d\n", result);
}

static void incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{

    tot_len = strlen(topic);
    memcpy(mbuf.topic, topic, tot_len);
    //    printf("Topic %s. %d\n", mbuf.topic, tot_len);
    //  printf("Topic %s. %d\n", topic, tot_len);
}

static void incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    memcpy(mbuf.data, data, len);

     //call external callback in main.c
  //  _ext_callback(mbuf.topic, mbuf.data);
    _ext_callback(ctx, &mbuf);

    memset(mbuf.topic,0,TOPIC_SIZE);
    memset(mbuf.data,0,MESSAGE_SIZE);
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED && client != NULL)
    {

        blink(3,25);
        mqtt_set_inpub_callback(client, incoming_publish_cb, incoming_data_cb, arg);
    }

    else{

        //commented out wi-fi reconnect, throws CYW43 error and hangs
       /* if(cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
            wifi_init();*/
        
        /* try reconnect */
        if(helper_connect(_id)!=ERR_OK) {

            // add logic to stop car

            /*

            blink(6, 50);
          //  sleep_ms(500);

            pwm_set_gpio_level(STEER_L,0);
            pwm_set_gpio_level(STEER_R,0);
            pwm_set_gpio_level(DRIVE_F,0);
            pwm_set_gpio_level(DRIVE_B,0);

            watchdog_enable(10,true);
            watchdog_start_tick(12);
            while(1);

            */
        }

    }
}





// ###################################################

/// @brief Connects locally defined callback to backend defined in this header file.
static void helper_set_message_decoder(void (*ext_callback)(void *ctx, struct message_buf *msg))
{

    _ext_callback = ext_callback;

}

static int helper_subscribe(char *topic)
{

    return mqtt_subscribe(client, topic, 1, sub_request_cb, NULL);

}

static int helper_unsubscribe(char *topic)
{

    return mqtt_unsubscribe(client, topic, sub_request_cb, NULL);

}


static int helper_publish(char *topic, char *payload, int qos)
{

    // u8_t qos = 2;        //changed to 0, 2 has issues with pico
    // u8_t retain = 0;

    return mqtt_publish(client, topic, payload, strlen(payload), qos, 0, pub_request_cb, NULL);

}


static int helper_publish_with_strlen(char *topic, char *payload, int qos, int len)
{

    // u8_t qos = 2;        //changed to 0, 2 has issues with pico
    // u8_t retain = 0;

    return mqtt_publish(client, topic, payload, len, qos, 0, pub_request_cb, NULL);

}


static void helper_set_id_for_reconnect(const char *id) {
    
    memcpy(_id,id,strlen(id));

}





// ################## Connectivity ###################

static void helper_disconnect()
{
    helper_unsubscribe(CTRL_TOPIC);
    mqtt_disconnect(client);
}


static int helper_connect(const char *id)
{
    if(client!=NULL)
        helper_disconnect();
        
    cyw43_arch_lwip_begin();
    client = mqtt_client_new();
    cyw43_arch_lwip_end();

    ci.client_id = id;//"rc_unassigned";
    mqtt_client_connect(client, &ip, 1883, mqtt_connection_cb, 0, &ci);

   // printf("ERR: %X",mqtt_client_connect(client, &ip, 1883, mqtt_connection_cb, 0, &ci));
    return helper_subscribe(CTRL_TOPIC);
}






// ###################################################

static int _mqtt_init(const char *id)
{

    memset(&ci, 0, sizeof(ci));

    return helper_connect(id);

}

static int mqtt_init(ip_addr_t host_ip, const char *id, void *in_ctx, void (*ext_callback)(void *ctx, struct message_buf *msg))
{

  //  wifi_init();
    ip = host_ip;
    int ret = _mqtt_init(id);
    helper_set_id_for_reconnect(id);
    helper_set_message_decoder(ext_callback);
    ctx = in_ctx;

    init_message_buf(&mbuf);




    return ret;


}

#endif

