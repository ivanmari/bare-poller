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
#include "PrecisionTimer.h"

PrecisionTimer::PrecisionTimer(Platform* plat, unsigned long timeout):m_plat(plat), m_timeStart(0), m_timeElapsed(0), m_timeout(timeout), m_active(false)
{
    //ctor
}

PrecisionTimer::~PrecisionTimer()
{
    //dtor
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
    long remaining_time = 0;
    if(m_active)
    {
        remaining_time = m_timeStart + m_timeout - m_plat->getSystemUpTimeMicros();
    }
    return remaining_time;
}
