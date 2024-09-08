#include <loRaWAN.h>
#include "hardware/uart.h"
#include <pico/stdlib.h>
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include <stdint.h> // Para uint8_t
#include <string.h> // Para strcat
#include <stdio.h>
// Inicialización de variables
char sendCmd[] = "AT+DTRX=0,2,62,";
char hex_message[256] = {0};
char send_message[256] = {0};
// Definición de la función de inicializacións

void on_uart_rx()
{
    while (uart_is_readable(UART_ID_LORA))
    {
        char received_char = uart_getc(UART_ID_LORA);
        printf("%c", received_char);
    }
}

bool send_message_to_uart(uint8_t *datos, uint8_t mem_address)
{
    uint8_t i = mem_address - 1;
    if (datos[i] != '}')
    {
        sprintf(&hex_message[i * 2], "%02x", datos[i]);
        return true;
    }
    else if (datos[i] == '}')
    {
        sprintf(&hex_message[i * 2], "%02x", datos[i]);
        // hex_message[i * 2] = '}';
        strcpy(send_message, sendCmd);
        strcat(send_message, hex_message);
        strcat(send_message, "\n");
        printf("%s\n", send_message);
        return false;
    }

    // El que lea esto es gay
}

void setup_uart_lora()
{
    // Se inicializa UART, defininiendole los pines, las funciones de los GPIO, etc.
    uart_init(UART_ID_LORA, BAUD_RATE_UART);
    gpio_set_function(LORA_TX, GPIO_FUNC_UART);
    gpio_set_function(LORA_RX, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID_LORA, false, false);
    uart_set_format(UART_ID_LORA, DATA_LEN, STOP_BITS, PARITY);

    // Se setea el handler de la interrupción UART y se habilita :D
    irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);
    irq_set_enabled(UART0_IRQ, true);

    // habilitamos el UART para enviar interrupciones - RX only
    uart_set_irq_enables(UART_ID_LORA, false, false);
}