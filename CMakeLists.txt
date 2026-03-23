cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Pull in FreeRTOS
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(rc_rtos C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(PICO_BOARD pico_w)

# Initialize the SDK
pico_sdk_init()

add_executable(rc_rtos 
    hooks.cpp 
    modules/Module.cpp 
    modules/PWMModule.cpp
    modules/WiFiModule.cpp
    modules/MQTTModule.cpp
    main.cpp 
)
set(PICO_BOARD pico_w)

target_include_directories(rc_rtos PRIVATE 
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
)
 
# pull in common dependencies
target_link_libraries(rc_rtos 
    pico_stdlib 
    FreeRTOS-Kernel 
    FreeRTOS-Kernel-Heap4
    pico_cyw43_arch_lwip_threadsafe_background 
    pico_lwip_arch
    pico_lwip_mqtt


    hardware_pwm
    
    )

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(rc_rtos)


pico_enable_stdio_usb(rc_rtos 1)   # or stdio_uart
pico_enable_stdio_uart(rc_rtos 0)