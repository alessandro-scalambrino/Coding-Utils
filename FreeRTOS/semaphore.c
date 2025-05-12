#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#define rtDelay(v) {vTaskDelay(v/15);}

//1. define Handle
SemaphoreHandle_t Binary_Semaphore;

void setup() {

Serial.begin(9600);
xTaskCreate(taskSerial1, "serial1", 128, NULL, 1, NULL);
xTaskCreate(taskSerial2, "serial2", 128, NULL, 1, NULL);

//2. create semaphore
Binary_Semaphore = xSemaphoreCreateBinary(); //--> xSemaphoreCreateMutex() for mutex

  /*Mutex → for resource protection (use like a lock).
Semaphore → for event signaling or resource counting.*/

  //3.release during setup
xSemaphoreGive(Binary_Semaphore);

}

void loop() {
  
}

void taskSerial1() {
  while(1) {
  //4.take semaphore if possible
  xSemaphoreTake(Binary_Semaphore, portMAX_DELAY); // (Semaphore, maxTrytime)
  Serial.println("Executing serial task 1");
  xSemaphoreGive(Binary_Semaphore); //release semaphore
  rtDelay(30);

  };
};

void taskSerial2() {
  while(1) {
  //5.same
  xSemaphoreTake(Binary_Semaphore, portMAX_DELAY); // (Semaphore, maxTrytime)
  Serial.println("Executing serial task 2");
  xSemaphoreGive(Binary_Semaphore); //release semaphore
  rtDelay(30);
  };
};
