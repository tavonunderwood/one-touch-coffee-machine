#include <Arduino.h>
#include "UserControls.h"
#include "pins.h"
#include "config.h"

namespace {
    unsigned long selectedMs = DEFAULT_GRIND_TIME_MS;
    uint8_t previousAB = 0;
    int8_t quadratureSum = 0;

    bool previousRawPressed = false;
    bool debouncedPressed = false;
    bool pendingPress = false;
    unsigned long lastRawChangeMs = 0;

    uint8_t readAB() {
        return (static_cast<uint8_t>(digitalRead(PIN_ENCODER_A)) << 1)
             | static_cast<uint8_t>(digitalRead(PIN_ENCODER_B));
    }

    void printDuration() {
        Serial.print(F("Selected grind duration: "));
        Serial.print(selectedMs / 1000UL);
        Serial.println(F(" s (push knob to start)"));
    }

    void moveSelection(int8_t direction) {
        if (ENCODER_REVERSE_DIRECTION) direction = -direction;
        if (direction > 0 && selectedMs <= MAX_GRIND_TIME_MS - GRIND_TIME_STEP_MS) {
            selectedMs += GRIND_TIME_STEP_MS;
            printDuration();
        } else if (direction < 0 && selectedMs >= MIN_GRIND_TIME_MS + GRIND_TIME_STEP_MS) {
            selectedMs -= GRIND_TIME_STEP_MS;
            printDuration();
        }
    }
}

namespace UserControls {
    void begin() {
        pinMode(PIN_ENCODER_A, INPUT_PULLUP);
        pinMode(PIN_ENCODER_B, INPUT_PULLUP);
        pinMode(PIN_ENCODER_BUTTON, INPUT_PULLUP);
        previousAB = readAB();
        previousRawPressed = (digitalRead(PIN_ENCODER_BUTTON) == LOW);
        debouncedPressed = previousRawPressed;
        lastRawChangeMs = millis();
        printDuration();
    }

    void update(bool allowDurationChange) {
        // Gray-code quadrature decoder. The lookup table rejects invalid
        // two-bit jumps and naturally cancels many contact bounces.
        static const int8_t transitionDelta[16] = {
             0, -1,  1,  0,
             1,  0,  0, -1,
            -1,  0,  0,  1,
             0,  1, -1,  0
        };
        const uint8_t ab = readAB();
        const uint8_t index = static_cast<uint8_t>((previousAB << 2) | ab);
        previousAB = ab;
        quadratureSum += transitionDelta[index];

        if (quadratureSum >= ENCODER_TRANSITIONS_PER_DETENT) {
            quadratureSum = 0;
            if (allowDurationChange) moveSelection(1);
        } else if (quadratureSum <= -static_cast<int8_t>(ENCODER_TRANSITIONS_PER_DETENT)) {
            quadratureSum = 0;
            if (allowDurationChange) moveSelection(-1);
        }

        const bool rawPressed = (digitalRead(PIN_ENCODER_BUTTON) == LOW);
        const unsigned long now = millis();
        if (rawPressed != previousRawPressed) {
            previousRawPressed = rawPressed;
            lastRawChangeMs = now;
        }
        if (now - lastRawChangeMs >= BUTTON_DEBOUNCE_MS &&
            rawPressed != debouncedPressed) {
            debouncedPressed = rawPressed;
            if (debouncedPressed) pendingPress = true;
        }
    }

    bool consumeButtonPress() {
        if (!pendingPress) return false;
        pendingPress = false;
        return true;
    }

    unsigned long selectedGrindTimeMs() { return selectedMs; }
}
