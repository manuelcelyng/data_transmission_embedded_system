// Inclusión de librerías necesarias -> api pico : High level APIs
#include <i2c_slave_mode.h>
#include <loRaWAN.h>

#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

// Configuración del esclavo

int main()
{
    stdio_init_all();
    setup_slave();
    // setup_uart_lora();

    while (true)
    {
        // Valido que ya hay data en el buffer para ser enviada por lora :D
        if (context.new_data)
        {
            // Envio el mensaje por UART -> LoRaWAN
            // La función retorna true mientras que aún no  haya encontrado el fin del mensaje para enviarlo
            context.new_data = send_message_to_uart(context.mem, context.mem_address);
            if (!context.new_data)
            {
                context.mem_address = 0; // Reinicio la dirección del buffer a 0
            }
        }
    }
}