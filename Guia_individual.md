#### Guía individual 

En la carpeta "Posix demostración" encontrará lo necesario para realizar la guía indiviual. 

1) Abra dicha carpeta con visual studio code. 

2) Modifique el archivo Makefile:

Para establer los PATH según el sitio donde haya descargado dicha carpeta. En específico, debe modificar: 

FREERTOS_DIR_REL := PATH_a_su/FreeRTOSv202212.01/FreeRTOS

FREERTOS_PLUS_DIR_REL := PATH_a_su/FreeRTOSv202212.01/FreeRTOS-Plus

3) Modifique el archivo c_cpp-properties.json lineas 7 y 8 pra su Path. 

4) Abra el archivo src/main.c 

En este archivo observará el código ejecutado en clase. Al final del documento se encontra el espacio identificado con #TO DO. 

Deberá generar una nueva tarea y realizar la instancia. 

Compile el programa y ejecute el archivo "ejectuble" tome una captura de la salida. y una captura del código modifica en main por su parte. 



Código fuente: https://github.com/FreeRTOS/FreeRTOS/releases/tag/202212.01
