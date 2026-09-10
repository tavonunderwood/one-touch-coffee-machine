#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Coffee machine controller starting");
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Coffee machine controller running");
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("OFF");
  delay(500);
}

