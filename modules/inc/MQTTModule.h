#include "Module.h"

#include "lwip/ip_addr.h"
#include "lwip/apps/mqtt.h"
#include <span>
#include <string>


class MQTTModule : public Module {

    enum QOS {
        QOS_0,
        QOS_1,
        QOS_2
    };



    public:

        int publish(std::string topic, std::span<const uint8_t> payload);
        int publish(std::string topic, std::span<const uint8_t> payload, QOS qos);

        int subscribe(std::string topic);


        int connect();
        void disconnect();

        MQTTModule(std::string host_ip, QOS defaultQOS = QOS_0);
        ~MQTTModule();


        virtual bool enable() {

            this->setEnabled(this->good_host_ip);

            if(this->isEnabled())
                return this->connect();
            return this->isEnabled();

        }

        virtual bool disable() {

            this->disconnect();
            this->setEnabled(false);
            return this->isEnabled();

        }

        int init();

        virtual void update(){}





    private:

        QOS defaultQOS = QOS_0;
        bool good_host_ip = false;
        ip_addr_t host_ip;
        std::string client_id = "";
        bool hasID = false;
      //  std::unordered_map<std::string, std::span> inbox;
};