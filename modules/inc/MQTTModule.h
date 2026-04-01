
#include "Module.h"

#include "lwip/ip_addr.h"
#include "lwip/apps/mqtt.h"
#include <span>
#include <cstring>
#include <string>
#include <queue>

extern "C" {
    #include "../../inc/mqtt_helper.h"
}


class MQTTModule : public Module {

    enum QOS {
        QOS_0,
        QOS_1,
        QOS_2
    };



    public:

        int publish(std::string topic, char * payload);
        int publish(std::string topic, std::span<const uint8_t> payload, QOS qos);

        int subscribe(std::string topic);


        int mqtt_connect();
        void mqtt_disconnect();

        MQTTModule();
        MQTTModule(std::string host_ip, QOS defaultQOS = QOS_0, std::string client_id = "rc_unassigned");
        ~MQTTModule();


        virtual bool enable() {
            this->setEnabled(this->good_host_ip);
            return this->isEnabled();
        }

        virtual bool disable() {

            this->mqtt_disconnect();
            this->setEnabled(false);
            return this->isEnabled();

        }

        virtual int init();

        virtual void update(){
        }

        message_buf dequeue();

        int getQueueSize() const {
            return this->msgqueue.size();
        }
    private:

        QOS defaultQOS = QOS_0;

        bool good_host_ip = false;
        ip_addr_t host_ip;

        bool hasID = false;
        std::string client_id = "";

        message_buf msgbuf;
        std::queue<message_buf> msgqueue; 


        static message_buf msg_deepcopy (message_buf * mb) {
            message_buf r_mb;
            std::memcpy(r_mb.topic,(const char*)mb->topic,strlen((const char*)mb->topic));
            std::memcpy(r_mb.data,(const char*)mb->data,mb->len);
            r_mb.isNewData = false;
            r_mb.len = mb->len;
            return r_mb;
        }

        static void enqueue(void * ctx, message_buf * msg) {
            
            if(ctx==nullptr)return;

            auto* self = static_cast<MQTTModule*>(ctx);

            if(self->getQueueSize() >= 64)
                return;
            self->msgqueue.push(msg_deepcopy(msg));
        }


        
      //  std::unordered_map<std::string, std::span> inbox;
};