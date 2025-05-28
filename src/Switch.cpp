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
