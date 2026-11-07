#pragma once

namespace FilterSystem {
    void turnCCW();
    void turnCW();
    void filterDispensed();
    void refillFilters();
    extern byte filtersRemaining;
    bool homing = false;
}