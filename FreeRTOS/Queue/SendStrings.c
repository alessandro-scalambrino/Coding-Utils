#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define rtDelay(v) vTaskDelay((v)/portTICK_PERIOD_MS)

//Declare queue handle
QueueHandle_t xQueue = NULL;
// Declare task handles
TaskHandle_t senderTaskHandle = NULL;
TaskHandle_t receiverTaskHandle = NULL;

void setup() {

  Serial.begin(9600);

  xQueue = xQueueCreate(5, sizeof(int)); // (numItem, itemSize)

  // Create sender task
  xTaskCreate(taskSender, "tx - send", 128, NULL, 1, &senderTaskHandle );

  // Create receiver task
  xTaskCreate(taskReceiver, "rx -receive", 128, NULL, 1, &receiverTaskHandle);
}

void loop() {
}

void taskSender(void *) {

  char* data[] = {"Hello", "world", "Hello", "world", "Hello", "world" };
  int datalen = 6;
  
  while (1) {
    
    xQueueSend(xQueue, &data, portMAX_DELAY); // (queuehandler, data to send, wateTime if queue is full)

    //send txt
    for (int i=0; i<datalen; i++) {
      xQueueSend(xQueue, &data[i], portMAX_DELAY);


      int occupiedSpotCount = uxQueueMessagesWaiting(xQueue); //--> return OCCUPIED QUEUE SPOT num
      int freeSpotCount = uxQueueSpacesAvailable(xQueue);  //--> return FREE SPOTS num

      Serial.print("Occupied spots: ");
      Serial.println(occupiedSpotCount);

      Serial.print("Free spots: ");
      Serial.println(freeSpotCount);

      Serial.println("Sent Data: ");
      Serial.println(data[i]);
    }
  }
}

void taskReceiver(void *) {

}
