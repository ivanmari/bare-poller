// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef BLINKER_H
#define BLINKER_H

#include "PrecisionTimer.h"
// Switch.h will be included by BarePoller.h or directly by user sketch if needed
// #include "Switch.h" 
#include "Platform.h" // Added Platform.h include

class Blinker
{
public:
    Blinker(Platform* plat, int output_pin, long int time_on, long int time_off, bool active_level);

    void execute();
    void reset();

private:
    Platform* m_plat;
    PrecisionTimer m_blinkOffTimer;
    PrecisionTimer m_blinkOnTimer;
    const int m_output_pin;
    const bool m_active_level;
};
#endif //BLINKER_H
