#include <Arduino_FreeRTOS.h>
#define rtDelay(v) vTaskDelay((v)/portTICK_PERIOD_MS)

const int blinkLed=13;


void setup() {

xTaskCreate
(
taskLedBlink,
"blink",
128,
NULL,
1,
NULL
);

xTaskCreate
(
taskSerial,
"serial",
128,
NULL,
1,
NULL
);

Serial.begin(9600);
}

void loop() {
  
}

void taskLedBlink() {
  
  digitalWrite(blinkLed, HIGH);
  rtDelay(500);
  digitalWrite(blinkLed, LOW);
  rtDelay(500);


};

void taskSerial() {
  Serial.println("Multithreading blinkng");
  rtDelay(500);

};
