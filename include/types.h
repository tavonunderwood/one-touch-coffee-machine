

#pragma once

#include <Arduino.h>

/*
 * ============================================================
 * Shared Types
 * ============================================================
 */

// ============================================================
// BREW STATE
// ============================================================

enum class MachineState
{
    IDLE,
    DOSING,
    GRINDING,
    WAITING_FOR_BREW,
    DISPOSING,
    ERROR
};

// ============================================================
// ERROR CODES
// ============================================================

enum class ErrorCode : uint8_t
{
    NONE,

    SCALE_NOT_READY,
    SCALE_READING_INVALID,
    BEAN_DISPENSER_TIMEOUT,

    GRINDER_TIMEOUT,

    WATER_PUMP_TIMEOUT,
    WATER_SENSOR_ERROR,

    TEMPERATURE_SENSOR_ERROR,
    HEATER_TIMEOUT,
    OVER_TEMPERATURE,

    UNKNOWN
};

// ============================================================
// BREW SETTINGS
// ============================================================

struct BrewSettings
{
    float beanMass_g;
    //float waterVolume_mL;
    //float brewTemperature_C;
};

// ============================================================
// SENSOR DATA
// ============================================================

struct SensorData
{
    float beanMass_g;
    float waterTemperature_C;
    float waterVolume_mL;
};

