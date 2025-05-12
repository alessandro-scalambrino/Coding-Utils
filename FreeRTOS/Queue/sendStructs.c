#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define rtDelay(v) vTaskDelay((v)/portTICK_PERIOD_MS)

typedef struct sensor {
  char* sensorName;
  char* sensorType;
  int sensorData;
  float sensorScaleUnit;
};

QueueHandle_t xQueue = NULL;
TaskHandle_t senderTaskHandle = NULL;
TaskHandle_t receiverTaskHandle = NULL;

void setup() {

  Serial.begin(9600);

  xQueue = xQueueCreate(5, sizeof(sensor)); // (numItem, itemSize)

  // Create sender task
  xTaskCreate(taskSender, "tx - send", 128, NULL, 1, &senderTaskHandle );

  // Create receiver task
  xTaskCreate(taskReceiver, "rx -receive", 128, NULL, 1, &receiverTaskHandle);
}

void loop() {
}

void taskSender(void *) {

  struct sensor tempSensor = {"XDB", "tempSensor", 56, 4.2};
  
  while (1) {
    
    xQueueSend(xQueue, &tempSensor, portMAX_DELAY); // (queuehandler, data to send, wateTime if queue is full)


    int occupiedSpotCount = uxQueueMessagesWaiting(xQueue); //--> return OCCUPIED QUEUE SPOT num
    int freeSpotCount = uxQueueSpacesAvailable(xQueue);  //--> return FREE SPOTS num

    Serial.print("Occupied spots: ");
    Serial.println(occupiedSpotCount);

    Serial.print("Free spots: ");
    Serial.println(freeSpotCount);

    Serial.print("SensorName: ");
    Serial.println(tempSensor.sensorName);
    
    Serial.print("SensorType ");
    Serial.println(tempSensor.sensorType);
    
    Serial.print("Sensor Data: ");
    Serial.println(tempSensor.sensorData);
    
    Serial.print("Data Scale: ");
    Serial.println(tempSensor.sensorScaleUnit);
   
  }
}

void taskReceiver(void *) {

}
