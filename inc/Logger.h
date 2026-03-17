#include "FreeRTOS.h"
#include "queue.h"






class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;  // Guaranteed to be destroyed and instantiated only once
        return instance;
    }

    QueueHandle_t xMsgQueue;


private:
    Logger() {

        xMsgQueue = xQueueCreate( 10, sizeof( unsigned long ) );


    }  // Private constructor to prevent instantiation

};