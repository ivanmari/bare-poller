// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef SWITCH_H
#define SWITCH_H

#include "PrecisionTimer.h"
#include "Platform.h"

const unsigned long DEBOUNCE_PERIOD = 20000; //microseconds


class Switch
{
public:
    // Modified constructor to take Platform* instead of ASi*
    Switch(Platform* platform, int pin, bool level, unsigned long debounce_period_us = DEBOUNCE_PERIOD);

    bool isOn();

private:
    int m_pin;
    bool m_active_level;
    PrecisionTimer m_debounceTimer;
    Platform* m_platform;
};
#endif //SWITCH_H
