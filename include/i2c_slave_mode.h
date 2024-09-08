#ifndef SLAVELIB_H
#define SLAVELIB_H

#include <pico/i2c_slave.h>
#include <pico/stdlib.h>

// Defino el address de la pico como esclavo
#define I2C_SLAVE_ADDRESS 0x17
#define I2C_BAUDRATE 100000 // 100KHZ

#define I2C_SLAVE_SDA_PIN PICO_DEFAULT_I2C_SDA_PIN // GPIO 4
#define I2C_SLAVE_SCL_PIN PICO_DEFAULT_I2C_SCL_PIN // GPIO 5

// Defino la estructura,
typedef struct
{
    uint8_t mem[256];
    uint8_t mem_address;
    bool mem_address_written;
    volatile bool new_data;
} Context;

// la defino externamente para que sea global
extern Context context;

//  Función que maneja la logica del i2c al recibir eventos de las interrupciones
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
// Función que configura el slave
void setup_slave();

#endif // SLAVELIB_H