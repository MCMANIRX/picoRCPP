#include "FreeRTOS.h"
#include "task.h"

void vApplicationTickHook(void) {
    // called every tick, empty for now
}

void vApplicationIdleHook(void) {
    // idle task hook, empty for now
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    (void)xTask;
    (void)pcTaskName;
    for(;;); // halt
}

void vApplicationMallocFailedHook(void) {
    for(;;); // halt
}