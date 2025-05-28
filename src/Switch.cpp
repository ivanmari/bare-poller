// Copyright (c) 2023 Google LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#include "Switch.h"
// const int DEBOUNCE_PERIOD = 0; //us // Made this a constructor argument with default 0

// Modified constructor
Switch::Switch(Platform* platform, int pin, bool level, unsigned long debounce_period_us):
    m_pin(pin), 
    m_active_level(level),
    m_debounceTimer(platform, debounce_period_us), // Use platform for timer
    m_platform(platform) 
{
    m_platform->setPinMode(m_pin, PIN_INPUT); // Set pin mode in constructor
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
