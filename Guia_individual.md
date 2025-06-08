#### Guía individual 

En la carpeta "Posix demostración" encontrará lo necesario para realizar la guía indiviual. 

1) Abra dicha carpeta con visual studio code. 

2) Modifique el archivo Makefile:

Para establer los PATH según el sitio donde haya descargado dicha carpeta. En específico, debe modificar: 

FREERTOS_DIR_REL := PATH_a_su/FreeRTOSv202212.01/FreeRTOS

FREERTOS_PLUS_DIR_REL := PATH_a_su/FreeRTOSv202212.01/FreeRTOS-Plus

3) Modifique el archivo c_cpp-properties.json lineas 7 y 8 para su Path. 

4) Abra el archivo src/main.c 

En este archivo observará el código ejecutado en clase. A lo largo del documento se encontrará los espacios identificados con #TO DO:

Cree una tarea de mayor prioridad que tengo un delay de 500 ms.

Compile el programa y ejecute el archivo "ejectuble" tome una captura de la salida y una captura del código modifica en main por su parte. 

Analice el resultado de la consola, ¿es el esperado?


Código fuente: https://github.com/FreeRTOS/FreeRTOS/releases/tag/202212.01
