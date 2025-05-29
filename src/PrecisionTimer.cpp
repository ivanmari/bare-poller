// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#include "PrecisionTimer.h"
#include <limits> // Required for std::numeric_limits

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
    unsigned long current_active_elapsed = 0;
    if (m_active) {
        current_active_elapsed = m_plat->getSystemUpTimeMicros() - m_timeStart; // Relies on unsigned arithmetic for wrap safety
    }

    unsigned long total_effective_elapsed;
    // Check for overflow before adding m_timeElapsed and current_active_elapsed
    // Note: (std::numeric_limits<unsigned long>::max)() is ULONG_MAX
    if (m_timeElapsed > 0 && current_active_elapsed > (std::numeric_limits<unsigned long>::max)() - m_timeElapsed) {
        total_effective_elapsed = (std::numeric_limits<unsigned long>::max)(); // Saturate at max
    } else {
        total_effective_elapsed = m_timeElapsed + current_active_elapsed;
    }

    return total_effective_elapsed >= m_timeout;
}

long
PrecisionTimer::remaining() const
{
    unsigned long current_total_elapsed;

    if (m_active) {
        unsigned long current_micros = m_plat->getSystemUpTimeMicros();
        unsigned long elapsed_in_current_run = current_micros - m_timeStart; // Relies on unsigned arithmetic for wrap safety

        // Check for overflow before adding m_timeElapsed and elapsed_in_current_run
        // Note: (std::numeric_limits<unsigned long>::max)() is ULONG_MAX
        if (m_timeElapsed > 0 && elapsed_in_current_run > (std::numeric_limits<unsigned long>::max)() - m_timeElapsed) {
            current_total_elapsed = (std::numeric_limits<unsigned long>::max)(); // Saturate at max
        } else {
            current_total_elapsed = m_timeElapsed + elapsed_in_current_run;
        }
    } else {
        current_total_elapsed = m_timeElapsed;
    }

    if (current_total_elapsed >= m_timeout) {
        return 0; // Timer has expired or exactly met timeout
    }

    return (long)(m_timeout - current_total_elapsed);
}
