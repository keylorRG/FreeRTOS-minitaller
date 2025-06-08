#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

// Pines para LEDs
const int ledHighPin = 8;
const int ledLowPin = 9;

// ==========================
// ELEMENTO: COLA (QUEUE)
// ==========================
// Esta cola se usa para pasar datos desde la tarea del "sensor" a la tarea del "actuador".
// Permite comunicación entre tareas de manera segura y sin bloqueo activo.
QueueHandle_t xSensorQueue;

// ==========================
// ELEMENTO: SEMÁFORO (SEMAPHORE / MUTEX)
// ==========================
// Se usa un semáforo tipo mutex para asegurar el acceso exclusivo al Serial,
// evitando colisiones cuando múltiples tareas quieren escribir al mismo tiempo.
SemaphoreHandle_t xSerialSemaphore;

// ==========================
// ELEMENTO: TAREA (TASK) - Sensor
// ==========================
// Esta tarea simula la lectura de un sensor de temperatura y envía el valor a la cola.
void TaskSensor(void *pvParameters) {
  int fakeTemp = 20;  // Temperatura base

  while (1) {
    // Simula cambios aleatorios entre -2 y +2
    fakeTemp += random(-2, 3);
    if (fakeTemp < 0) fakeTemp = 0;

    // Enviar valor simulado a la cola (bloquea si la cola está llena)
    xQueueSend(xSensorQueue, &fakeTemp, portMAX_DELAY);

    // Esperar 1 segundo antes de volver a ejecutar
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// ==========================
// ELEMENTO: TAREA (TASK) - Actuador
// ==========================
// Esta tarea recibe el valor de temperatura desde la cola y enciende el LED apropiado.
// También imprime la temperatura usando un semáforo para sincronizar el acceso al Serial.
void TaskActuator(void *pvParameters) {
  int receivedTemp;

  while (1) {
    // Espera hasta recibir un dato de la cola (bloqueo indefinido)
    if (xQueueReceive(xSensorQueue, &receivedTemp, portMAX_DELAY) == pdPASS) {
      // Controlar LEDs según el valor recibido
      if (receivedTemp > 25) {
        digitalWrite(ledHighPin, HIGH);
        digitalWrite(ledLowPin, LOW);
      } else {
        digitalWrite(ledHighPin, LOW);
        digitalWrite(ledLowPin, HIGH);
      }

      // Acceso sincronizado al Serial usando semáforo
      if (xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
        Serial.print("Temperatura simulada: ");
        Serial.println(receivedTemp);
        xSemaphoreGive(xSerialSemaphore);
      }
    }
  }
}

// ==========================
// ELEMENTO: CONFIGURACIÓN INICIAL
// ==========================
void setup() {
  Serial.begin(9600);
  while (!Serial); // Espera a que el monitor serial esté listo

  pinMode(ledHighPin, OUTPUT);
  pinMode(ledLowPin, OUTPUT);

  // Crear cola de 10 elementos tipo int
  xSensorQueue = xQueueCreate(10, sizeof(int));
  if (xSensorQueue == NULL) {
    Serial.println("Error al crear la cola.");
    while (1); // Detener si falla la creación
  }

  // Crear semáforo tipo mutex para el Serial
  xSerialSemaphore = xSemaphoreCreateMutex();
  if (xSerialSemaphore == NULL) {
    Serial.println("Error al crear el semáforo.");
    while (1); // Detener si falla la creación
  }

  // ==========================
  // ELEMENTO: CREACIÓN DE TAREAS
  // ==========================
  // Crear tarea del sensor con prioridad 2
  xTaskCreate(TaskSensor, "Sensor", 128, NULL, 2, NULL);
  
  // Crear tarea del actuador con prioridad 3 (más alta)
  xTaskCreate(TaskActuator, "Actuador", 128, NULL, 3, NULL);
}

// ==========================
// ELEMENTO: LOOP PRINCIPAL
// ==========================
// En FreeRTOS, loop() no se utiliza como en Arduino tradicional.
// El control lo toma el planificador de tareas de FreeRTOS.
void loop() {
  // No se usa cuando se trabaja con FreeRTOS en Arduino.
}


