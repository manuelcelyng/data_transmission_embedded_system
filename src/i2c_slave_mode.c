#include <i2c_slave_mode.h>

// Definición de la variable
Context context = {
    .mem = {0},                   // Inicializa todos los elementos de mem a 0
    .mem_address = 0,             // Inicializa mem_address a 0
    .mem_address_written = false, // Inicializa mem_address_written a false
    .new_data = false,            // Inicializa a falso, esta es la bandera para enviar por UART
};

// Definición del handler, el cual es llamado desde el I2C ISR el cual debe completarse lo más rapido posible
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event)
{
    switch (event)
    {
    case I2C_SLAVE_RECEIVE: // El maestro ha escrito algo de información
        if (!context.mem_address_written)
        {
            // La escritura siempre inicia con la direccion de memoria
            context.mem_address = i2c_read_byte_raw(i2c);
            context.mem_address_written = true;
        }
        else
        {
            // Guardo en la memoria
            context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
            context.mem_address++;
            context.new_data = true;
        }
        break;
    case I2C_SLAVE_REQUEST: // El maestro está solicitando data
        // lo carga de la memoria
        i2c_write_byte_raw(i2c, context.mem[context.mem_address]);
        context.mem_address++;
        break;
    case I2C_SLAVE_FINISH: // El maestro envia la señal de Stop / Restart
        context.mem_address_written = false;
        break;
    default:
        break;
    }
}

void setup_slave()
{
    gpio_init(I2C_SLAVE_SDA_PIN);                        // Inicializo el GPIO SDA
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C); // Seteo el GPIO en modo I2C
    gpio_pull_up(I2C_SLAVE_SDA_PIN);

    gpio_init(I2C_SLAVE_SCL_PIN);                        // Inicializo el GPIO DEL SCL
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C); // Seteo el GPIO en modo I2C
    gpio_pull_up(I2C_SLAVE_SCL_PIN);

    i2c_init(i2c0, I2C_BAUDRATE); // Inicializo el canal I2C0 con su respectiva velocidad de transferencia

    i2c_slave_init(i2c0, I2C_SLAVE_ADDRESS, &i2c_slave_handler); // Inicio el manejador del esclavo y le asigno su dirección de memoria
}