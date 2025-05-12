#include <Arduino_FreeRTOS.h>

#define rtDelay(v) vTaskDelay((v)/portTICK_PERIOD_MS)

const int blinkLed = 13;

// Declare task handles
TaskHandle_t blinkTaskHandle = NULL;
TaskHandle_t serialTaskHandle = NULL;

void setup() {
  pinMode(blinkLed, OUTPUT);
  Serial.begin(9600);

  // Create LED blink task
  xTaskCreate(
    taskLedBlink,
    "blink",
    128,
    NULL,
    1,
    &blinkTaskHandle    // <-- Task handler
  );

  // Create Serial print task
  xTaskCreate(
    taskSerial,
    "serial",
    128,
    NULL,
    1,
    &serialTaskHandle   // <-- Task handler
  );
}

void loop() {
}

// LED Blink Task
void taskLedBlink(void *pvParameters) {
  (void) pvParameters;

  while (1) {
    digitalWrite(blinkLed, HIGH);
    rtDelay(500);
    digitalWrite(blinkLed, LOW);
    rtDelay(500);
  }
}

// Serial Task
void taskSerial(void *pvParameters) {
  (void) pvParameters;

  while (1) {
    Serial.println("Multithreading blinking");
    rtDelay(1000);

    // Example: Suspend LED blinking after 5 seconds
    static int counter = 0;
    counter++;
    if (counter == 5) {
      Serial.println("Suspending LED task");
      vTaskSuspend(blinkTaskHandle);
      rtDelay(2000);
      Serial.println("Resuming LED task");
      vTaskResume(blinkTaskHandle);
    }
  }
}
