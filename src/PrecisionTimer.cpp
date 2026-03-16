// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BareMetalPoller authors
// This file is part of BareMetalPoller, licensed under the MIT License. See LICENSE file for details.

#include "PrecisionTimer.h"

PrecisionTimer::PrecisionTimer(Platform* plat, unsigned long timeout):m_plat(plat), m_timeStart(0), m_timeElapsed(0), m_timeout(timeout), m_active(false)
{
}

void
PrecisionTimer::start()
{
    if(!m_active)
    {
        m_active = true;
        m_timeStart = m_plat->getSystemUpTimeMicros();
    }
}

bool
PrecisionTimer::running() const
{
    return m_active;
}

bool
PrecisionTimer::stopped() const
{
    return !m_active;
}

void
PrecisionTimer::stop()
{
    m_active = false;
    m_timeElapsed = m_plat->getSystemUpTimeMicros() - m_timeStart;
}

void
PrecisionTimer::reset()
{
    m_active = false;
    m_timeStart = 0;
    m_timeElapsed = 0;
}

bool
PrecisionTimer::expired() const
{
    bool ret = false;
    unsigned long currently_elapsed = 0;

    if(m_active)
    {
        currently_elapsed = m_plat->getSystemUpTimeMicros() - m_timeStart;
    }

    if (m_timeElapsed + currently_elapsed >= m_timeout)
    {
        ret = true;
    }
    return ret;
}

long
PrecisionTimer::remaining() const
{
    unsigned long currently_elapsed = 0;
    if (m_active) {
        currently_elapsed = m_plat->getSystemUpTimeMicros() - m_timeStart;
    }

    unsigned long total_elapsed = m_timeElapsed + currently_elapsed;

    if (total_elapsed >= m_timeout) {
        return 0;
    }

    return m_timeout - total_elapsed;
}
