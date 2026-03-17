#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "modules/inc/PWMModule.h"
#include "modules/inc/WiFiModule.h"
#include "task.h"
#include <cstdio>

#include "inc/rc_config.h"

void vBlinkTask(void * params) {

   for (;;) {

   //   gpio_put(PICO_DEFAULT_LED_PIN, 1);

      vTaskDelay(250);

   //   gpio_put(PICO_DEFAULT_LED_PIN, 0);

      vTaskDelay(250);


   }

}


int main() {

   stdio_init_all();

   PWMModule p(DRIVE_F,DRIVE_B,30000L);


               WiFiModule m_wifi(SSID,PASS);
               if(m_wifi.enable())
                  for(;;){
                     printf("RSSI: %d\n",m_wifi.getRSSI());
                     sleep_ms(1000);
                  }



  // xTaskCreate(vWifiTask, "Drive", 128, NULL, 1, NULL);



 //  vTaskStartScheduler();

   return 0;

}

