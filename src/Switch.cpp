// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#include "Switch.h"

Switch::Switch(Platform* platform, int pin, bool level, unsigned long debounce_period_us):
    m_pin(pin), 
    m_active_level(level),
    m_debounceTimer(platform, debounce_period_us),
    m_platform(platform) 
{
    m_platform->setPinMode(m_pin, PIN_INPUT);
}

bool
Switch::isOn()
{
    bool current_pin_state = m_platform->getPin(m_pin);

    if (current_pin_state == m_active_level)
    {
        if (!m_debounceTimer.running())
        {
            m_debounceTimer.start();
        }
        else if (m_debounceTimer.expired())
        {
            return true; // Stable active state
        }
    }
    else // Pin is not at active level
    {
        if (m_debounceTimer.running()) // If it was running (potential bounce or release)
        {
            m_debounceTimer.reset(); // Reset timer
        }
    }
    return false; // Not stable active, or not active
}
