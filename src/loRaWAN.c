#include <loRaWAN.h>
#include "hardware/uart.h"
#include <pico/stdlib.h>
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include <stdint.h> // Para uint8_t
#include <string.h> // Para strcat
#include <stdio.h>
#include <debug.h>
// Inicialización de variables
char sendCmd[] = "AT+SENDB=0,2,98,"; // conf, portf, hex_payload en bytes EJEMPLO <- NO SE USA esta variable
const uint8_t conf = 0;
const uint8_t fport = 2;

char hex_payload[256] = {0};
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

bool send_message_to_uart(uint8_t *payload, uint8_t mem_address)
{
    uint8_t i = mem_address - 1;
    if (payload[i] != '}')
    {
        sprintf(&hex_payload[i * 2], "%02x", payload[i]);
        return true;
    }
    else if (payload[i] == '}')
    {
        int length_payload = strlen(payload);             // Coge el tamaño del payload que representa -> # de bytes a enviar
        sprintf(&hex_payload[i * 2], "%02x", payload[i]); // Agrega el ultimo valor en hexa
        hex_payload[(i + 1) * 2] = '\0';                  // le agrega el final de cadena al hex_payload

        // Preparamos el comando y obtenemos su valor en bytes
        int written = snprintf(send_message, sizeof(send_message), "AT+SENDB=%u,%u,%u,%s\n", conf, fport, length_payload, hex_payload);
        if (written < 0 || written >= sizeof(send_message))
        {
            safe_printf("Error: sending buffer exceeded or error formating.\n");
            return false;
        }

        // Imprimimos en el puerto serial
        safe_printf("message: %s\n", hex_payload);
        safe_printf("command: %s\n", send_message);
        uart_puts(UART_ID_LORA, send_message);

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
    uart_set_fifo_enabled(UART_ID_LORA, false);
    sleep_ms(500);

    // Se setea el handler de la interrupción UART y se habilita :D
    irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);
    irq_set_enabled(UART0_IRQ, true);

    // habilitamos el UART para enviar interrupciones - RX only
    uart_set_irq_enables(UART_ID_LORA, false, false);
}