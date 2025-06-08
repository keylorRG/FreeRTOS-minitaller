//Ejemplo para interiorizar los conceptos de tareas, planificador, multitarea. 


// Librerías estándar de C
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

// Librerías del kernel de FreeRTOS
#include "FreeRTOS.h"
#include "task.h"


// Declaración (prototipo) de las funciones que serán las tareas
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
// to do: prototipo de su función de la tarea 


/* ============================= */
/*            MAIN              */
/* ============================= */

int main(void)
{
    // Crear la primera tarea:
    // - Función: vTask1
    // - Nombre: "Task 1"
    // - Stack: 1024 palabras
    // - Parámetros: NULL (no se usan)
    // - Prioridad: 1
    // - Handle: NULL (no se guarda el identificador de la tarea)
    xTaskCreate(&vTask1, "Task 1", 1024, NULL, 1, NULL);

    // Crear la segunda tarea con los mismos parámetros
    xTaskCreate(&vTask2, "Task 2", 1024, NULL, 1, NULL);

    //to do:  Crear su tarea con mayor prioridad (prioridad 2) 


    // Iniciar el scheduler: esto pone en marcha el sistema operativo y nunca regresa
    vTaskStartScheduler();

    // Este punto no debería alcanzarse nunca, a menos que ocurra un error
    return 0;
}

/* ============================= */
/*         TAREA 1              */
/* ============================= */

void vTask1(void *pvParameters)
{
    (void) pvParameters; // Evita warnings si no se usa el parámetro

    for (;;)
    {
        // Imprimir mensaje en consola
        printf("<<Tarea 1>>\r\n");

        // Esperar 1000 milisegundos (1 segundo)
        vTaskDelay(pdMS_TO_TICKS(1000));
        //Al usar vTaskDelay, las tareas entran en estado Blocked, y luego vuelven a Ready cuando termina el tiempo.
    }
}

/* ============================= */
/*         TAREA 2              */
/* ============================= */

void vTask2(void *pvParameters)
{
    (void) pvParameters; // Evita warnings si no se usa el parámetro

    for (;;)
    {
        // Imprimir mensaje en consola
        printf("<<Tarea 2>>\r\n");

        // Esperar 1000 milisegundos (1 segundo)
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
/* ============================= */
/*         to do: Su tarea       */
/* ============================= */
/* Tarea de alta prioridad: imprime cada 500 ms */
