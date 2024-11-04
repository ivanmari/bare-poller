#include "ASi.h"
#include "Switch.h"

const int DEBOUNCE_PERIOD = 0; //us

Switch::Switch(int m_pin, bool level, ASi* asi):m_pin(m_pin), m_active_level(level),
    m_debounceTimer(asi->getPlatform(), DEBOUNCE_PERIOD), m_platform(asi->getPlatform()) {}

bool
Switch::isOn()
{
    bool switchStat = false;

    if (m_platform->getPin(m_pin) == m_active_level)
    {
        if(m_debounceTimer.running())
        {
            if(m_debounceTimer.expired())
            {
                switchStat = true;
            }
        }
        else
        {
            m_debounceTimer.start();
        }
    }
    else
    {
        m_debounceTimer.reset();
    }

    return switchStat;
}

