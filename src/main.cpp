#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

//Pins
uint8_t ROTOR_PIN;
uint8_t GRINDER_POWER_PIN;
uint8_t GRINDER_DIR_PIN;

void setup() 
{


  Serial.begin(115200);
  //Set output pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ROTOR_PIN, OUPUT);
  pinMode(GRINDER_POWER_PIN, OUPUT);
  pinMode(GRINDER_DIR_PIN, OUTPUT);
  //Set input pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(ROTARY_ENCODER_PIN_A, INPUT);
  pinMode(LOAD_SENSOR_PIN, INPUT);
  

  Serial.println("Coffee machine controller starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  MachineController::updateMachine();
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Coffee machine controller running");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("OFF");
  delay(500);
}

