// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef PRECISIONTIMER_H
#define PRECISIONTIMER_H

#include "Platform.h"

// Note on System Timer Wrap-Around:
// This timer relies on Platform::getSystemUpTimeMicros(). On platforms like Arduino,
// the underlying micros() function typically returns a 32-bit unsigned long value
// which wraps around after approximately 71.6 minutes.
// For PrecisionTimer to function correctly (especially for expired() and remaining()
// to be accurate), the 'timeout' duration given to the constructor should be less
// than this platform-specific wrap-around period.
// If a timeout exceeding this period is used, the timer may not report as expired
// when it should, and remaining() will yield incorrect results.
// This limitation is generally not a concern on platforms using a monotonic clock
// with a much larger wrap period (e.g., X86Platform with std::chrono::steady_clock).
class PrecisionTimer
{
public:
    /**
     * @brief Constructs a PrecisionTimer.
     * @param plat Pointer to the platform interface for time functions.
     * @param timeout Timeout in microseconds. IMPORTANT: See class-level note
     *                regarding system timer wrap-around and maximum effective timeout.
     */
    PrecisionTimer(Platform* plat, unsigned long timeout);

    virtual void stop();
    virtual void start();
    virtual void reset();

    virtual bool running() const;
    virtual bool stopped() const;
    virtual bool expired() const;
    virtual long remaining() const;

protected:

private:
    Platform*  m_plat;
    unsigned long m_timeStart;
    unsigned long m_timeElapsed;
    unsigned long m_timeout;
    bool m_active;
};
#endif // PRECISIONTIMER_H
