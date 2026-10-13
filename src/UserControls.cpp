#include <Arduino.h>
#include "UserControls.h"
#include "pins.h"
#include "config.h"

namespace 
{
    unsigned long selectedMs = DEFAULT_GRIND_TIME_MS;
    uint8_t previousAB = 0;
    int8_t quadratureSum = 0;

    bool previousRawPressed = false;
    bool debouncedPressed = false;
    bool pendingPress = false;
    unsigned long lastRawChangeMs = 0;
    // Reads the current state of the encoder pins as a two-bit value.
    //Example: if PIN_ENCODER_A is HIGH and PIN_ENCODER_B is LOW, this function returns 0b10 (2).
    uint8_t readAB() 
    {
        return (static_cast<uint8_t>(digitalRead(PIN_ENCODER_A)) << 1)
             | static_cast<uint8_t>(digitalRead(PIN_ENCODER_B));
    }
    // Prints the currently selected grind duration to the serial monitor.
    void printDuration() {
        Serial.print(F("Selected grind duration: "));
        // Print the selected grind duration in seconds.
        Serial.print(selectedMs / 1000UL);
        Serial.println(F(" s (push knob to start)"));
    }
    // Adjusts the selected grind duration based on the direction of the encoder turn.
    void moveSelection(int8_t direction) 
    
    {
        // Reverse the direction if the encoder is configured to be reversed.
        if (ENCODER_REVERSE_DIRECTION) direction = -direction;
        // Increase the selected grind duration if the direction is positive and within the allowed range.
        if (direction > 0 && selectedMs <= MAX_GRIND_TIME_MS - GRIND_TIME_STEP_MS) 
        {
            selectedMs += GRIND_TIME_STEP_MS;
            printDuration();
        } 
        // Decrease the selected grind duration if the direction is negative and within the allowed range.
        else if (direction < 0 && selectedMs >= MIN_GRIND_TIME_MS + GRIND_TIME_STEP_MS) 
        {
            selectedMs -= GRIND_TIME_STEP_MS;
            printDuration();
        }
    }
}

namespace UserControls 
{
    void begin() 
    {
        //INPUT_PULLUP is HIGH when the button is not pressed and LOW when pressed.
        pinMode(PIN_ENCODER_A, INPUT_PULLUP);
        pinMode(PIN_ENCODER_B, INPUT_PULLUP);
        pinMode(PIN_ENCODER_BUTTON, INPUT_PULLUP);
        // Initialize the previous state of the encoder and button.
        previousAB = readAB();
        // Read the initial state of the button.
        previousRawPressed = (digitalRead(PIN_ENCODER_BUTTON) == LOW);
        // Initialize the debounced state and timestamp for the button.
        debouncedPressed = previousRawPressed;
        // Initialize the timestamp for the last raw change.
        lastRawChangeMs = millis();
        // Print the initial grind duration to the serial monitor.
        printDuration();
    }

    void update(bool allowDurationChange) 
    {
        // Gray-code quadrature decoder. The lookup table rejects invalid
        // two-bit jumps and naturally cancels many contact bounces.

        //Represents valid transitions for the quadrature encoder.
        static const int8_t transitionDelta[16] = 
        {
             0, -1,  1,  0,
             1,  0,  0, -1,
            -1,  0,  0,  1,
             0,  1, -1,  0
        };

        static uint8_t lastAB = 255;
        const uint8_t ab = readAB();
        //TODO: Remove or refine this debug output for the encoder AB states.
        // if (ab != lastAB)
        // {
        //     Serial.print("Encoder AB: ");
        //     Serial.println(ab);
        //     lastAB = ab;
        // }
        // static unsigned long lastPrint = 0;

        // if (millis() - lastPrint >= 200)
        // {
        //     lastPrint = millis();

        //     Serial.print("A: ");
        //     Serial.print(digitalRead(PIN_ENCODER_A));

        //     Serial.print("  B: ");
        //     Serial.println(digitalRead(PIN_ENCODER_B));
        // }
        // Combine the previous and current AB states to form an index into the transition table.
        // static cast to ensure the index is of type uint8_t.
        //<< operator combines the previous and current AB states into a single index.
        const uint8_t index = static_cast<uint8_t>((previousAB << 2) | ab);
        previousAB = ab;
        // Update the quadrature sum based on the transition delta.
        quadratureSum += transitionDelta[index];
        // Check if the quadrature sum has reached the threshold for a detent. Could be 2 or 4
        if (quadratureSum >= ENCODER_TRANSITIONS_PER_DETENT) 
        {
            quadratureSum = 0;
            //If the detent threshold is reached and duration changes are allowed, move the selection.
            if (allowDurationChange) moveSelection(1);
        } 
        else if (quadratureSum <= -static_cast<int8_t>(ENCODER_TRANSITIONS_PER_DETENT)) 
        {
            quadratureSum = 0;
            if (allowDurationChange) moveSelection(-1);
        }

        const bool rawPressed = (digitalRead(PIN_ENCODER_BUTTON) == LOW);
        const unsigned long now = millis();
        if (rawPressed != previousRawPressed) 
        {
            previousRawPressed = rawPressed;
            lastRawChangeMs = now;
        }
        if (now - lastRawChangeMs >= BUTTON_DEBOUNCE_MS && rawPressed != debouncedPressed) 
        {
            debouncedPressed = rawPressed;
            if (debouncedPressed) pendingPress = true;
        }
    }

    bool consumeButtonPress() 
    {
        if (!pendingPress) return false;
        pendingPress = false;
        return true;
    }

    unsigned long selectedGrindTimeMs() { return selectedMs; 
    }
}
