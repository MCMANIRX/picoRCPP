#include "lwip/ip_addr.h"
#include "lwip/apps/mqtt.h"
#include "Module.h"



class MQTTModule : public Module {

    enum QOS {
        QOS_0,
        QOS_1,
        QOS_2
    };

    mqtt_client_t *client;

    public:

        int publish(std::string topic, std::span<const uint8_t> payload);
        int publish(std::string topic, std::span<const uint8_t> payload, QOS qos);


        int subscribe(std::string topic);

        int connect(std::string client_id);
        void disconnect();

        MQTTModule(std::string host_ip, QOS defaultQOS = QOS_0);
        ~MQTTModule();

    private:
        QOS defaultQOS = QOS_0;
        std::unordered_map<std::string, std::span> inbox;
};