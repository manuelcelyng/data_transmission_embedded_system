#ifndef LORA_H
#define LORA_H

#include <pico/stdlib.h>

#define UART_ID_LORA uart0  // CANAL UART USADO
#define BAUD_RATE_UART 9600 // BAUDIOS
#define LORA_TX 12          // GPIO 12
#define LORA_RX 13          // GPIO 13
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE // SIN PARIDAD

#define DATA_LEN 8

extern char sendCmd[];   // Define un  comando AT de inicialización
extern char message[16]; // Commands monitor serial

// Funcion donde se inicializa UART para el modulo LoRaWAN
void setup_uart_lora();
// Función que maneja la interrupción generada en el UART
void on_uart_rx();

// Función envía el mensaje por UART y retorna el estado del envío
bool send_message_to_uart(uint8_t *datos, uint8_t mem_address);

#endif
