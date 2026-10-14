#include <Arduino.h>
#include "MachineController.h"
#include "config.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    initializeMachine();
}

void loop() {
    // No delay(): responsive encoder, push-to-start/cancel and timed states.
    updateMachine();
}

// #include <Arduino.h>
// #include <Servo.h>

// // Servo configuration
// Servo filterServo;

// constexpr uint8_t PIN_FILTER_SERVO = 11;

// // Servo positions
// constexpr uint8_t FILTER_HOME_ANGLE_DEG = 55;
// constexpr uint8_t FILTER_DUMP_ANGLE_DEG = 28;

// // Timing
// constexpr unsigned long FILTER_DUMP_HOLD_MS = 3000UL;
// constexpr unsigned long FILTER_RETURN_SETTLE_MS = 1500UL;

// // Move servo to home position
// void moveHome()
// {
//     filterServo.write(FILTER_HOME_ANGLE_DEG);
//     Serial.println("Filter returning home");
// }

// // Move servo to disposal position
// void moveToDump()
// {
//     filterServo.write(FILTER_DUMP_ANGLE_DEG);
//     Serial.println("Filter dumping grounds");
// }

// void setup()
// {
//     Serial.begin(115200);

//     // Set initial target before enabling servo pulses
//     filterServo.write(FILTER_HOME_ANGLE_DEG);

//     // Attach HPS-2527 servo
//     filterServo.attach(PIN_FILTER_SERVO, 500, 2500);

//     Serial.println("Filter servo test starting");

//     delay(FILTER_RETURN_SETTLE_MS);
// }

// void loop()
// {
//     // Rotate to disposal position
//     moveToDump();
    // for (int i = 0; i < 25; i ++)
    // {
    //  filterServo.write(30);
    // delay(100);
    // filterServo.write(26);
    // delay(100);
    // }

//     // Hold at disposal position for 3 seconds
//     delay(FILTER_DUMP_HOLD_MS);

//     // Return to starting position
//     moveHome();

//     // Wait for servo to return before repeating
//     delay(FILTER_RETURN_SETTLE_MS);
// }