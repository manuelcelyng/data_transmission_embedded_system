cmake_minimum_required(VERSION 3.21)
set(PICO_BOARD pico_w)
include(pico_sdk_import.cmake)

project(I2C_VIM_PICO C CXX ASM)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)




pico_sdk_init()

add_executable(${PROJECT_NAME}
    src/main.c
    src/i2c_slave_mode.c
    src/loRaWAN.c
    src/debug.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC include/
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_i2c_slave
    pico_cyw43_arch_none
    hardware_i2c
    hardware_uart
    hardware_irq
    pico_stdio_uart
    )




pico_add_extra_outputs(${PROJECT_NAME})
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)