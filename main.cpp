#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "modules/inc/PWMModule.h"
#include "modules/inc/WiFiModule.h"
#include "modules/inc/MQTTModule.h"
#include "task.h"
#include <cstdio>

#include "inc/rc_config.h"


void vBlinkTask(void * params) {


      for (;;) {

     // gpio_put(ULT_LED_PIN, 1);

      vTaskDelay(250);

  //    gpio_put(ULT_LED_PIN, 0);
  // printf("hi\n");

      vTaskDelay(250);


   }
         while(1);



}

void wifiThread() {

   
         WiFiModule m_wifi(SSID,PASS);
         MQTTModule m_mqtt(std::string(STATIC_HOST_IP));

         m_wifi.enable();
         if(m_wifi.connect()) {

           if(m_mqtt.enable()) {
               m_mqtt.init();

               while(1){
               sleep_ms(1000);
               m_mqtt.publish(RC_TOPIC,ASSIGN_REQ);
               printf("%d\n",m_mqtt.getQueueSize());
               }
            }
         }
}


int main() {

   stdio_init_all();

   //wifiThread();
   PWMModule p(DRIVE_F,DRIVE_B,30000L);
   gpio_init(ULT_LED_PIN);
   gpio_set_dir(ULT_LED_PIN,GPIO_OUT);

  multicore_launch_core1(wifiThread);


          /*   for(;;){
                     printf("RSSI: %d\n",m_wifi.getRSSI());
                     sleep_ms(1000);
    
                     }*/
                    /*
   MQTTModule m_mqtt(std::string(STATIC_HOST_IP));
   if(!m_mqtt.enable()){
      


      /*for(;;){
         printf("RSSI: %d\n",m_wifi.getRSSI());
         sleep_ms(1000);
      }
   }*/

  // while(1) {
  //    printf("msgs: %d\n",m_mqtt.getQueueSize());

 //  }

 
sleep_ms(1000);


   xTaskCreate(vBlinkTask, "Drive", 128, NULL, 1, NULL);



   vTaskStartScheduler();


while(1);

   return 0;

}

