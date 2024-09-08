Información Importante para usar en la VIM3:
Instalar los siguientes paquetes para programar en C:   
    sudo apt intall build-essential
    sudo apt update
    sudo apt install build-essential
    sudo apt install i2c-tools libi2c-dev

Importancia de los paquetes anteriormente instalados:
    - build-essential : es un metapaquete que instala un conjunto de herramientas necesarias para compilar software en sistemas basados en debian/ubuntu, como en la VIM3
    ¿Que incluye? : 
        - gcc  : (GNU) Compiler collection : Compilador de C/C++
        - g++  : Compilador de C++
        - make : Herramienta que gestiona la compilación de proyectos que tienen multiples archivos fuentes
        - libc6-dev : Bibliotecas de desarrollo de C estandar y archivos de cabecera

    - i2c-tools: es un paquete que proporciona una serie de utilidades en línea de comandos para interactuar con el bus I2C en Linux.
    ¿Que incluye? :
        - i2cdetect : Escanea el bus I2C y muestra las direcciones de los dispositivos conectados
        - i2cdump   : Muestra el contenido de la memoria de un dispositivo I2C.
        - i2cget    : Lee un byte o palabra de un dispositivo I2C.
        - i2cset    : Escribe un byte o palabra en un dispositivo I2C

    - libi2c-dev :  es el paquete de desarrollo que incluye los archivos de cabecera y bibliotecas necesarias para escribir programas que interactúan con el bus I2C.
    ¿Que incluye? :
        - Archivos de cabecera como (i2c-dev.h) : estos archivos son necesarios para que el compilador entienda las funciones y macros relacionadas con I2C cuando estás escribiendo código en C.
        


Librerias importantes para añadir al código y gestionar I2C:
    #include <fcntl.h>
    #include <unistd.h
    #include <linux/i2c-dev.h>
    #include <sys/ioctl.h>

Resumen del Propósito de Cada Librería
    Entrada y Salida (stdio.h, unistd.h): Para manejar interacciones con el usuario, entrada y salida de datos.
    Gestión de Memoria y Procesos (stdlib.h): Para gestionar la memoria dinámica y el control de procesos.
    Control de Dispositivos (fcntl.h, ioctl.h): Para manejar archivos y dispositivos como el bus I2C en sistemas Linux.
    Manipulación de Cadenas y Memoria (string.h, stdint.h): Para trabajar con cadenas de texto y garantizar el manejo preciso de datos en la memoria.
    Interacción con I2C (i2c-dev.h): Específicamente para manejar la comunicación a través del bus I2C en Linux.