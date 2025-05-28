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
#include "Blinker.h"
// #include "Armed.h" // Removed missing include
// #include "io_defs.h" // Removed project-specific include

Blinker::Blinker(Platform* plat, int output_pin, long int time_on, long int time_off, bool active_level):
m_plat(plat),
m_active_level(active_level),
m_output_pin(output_pin),
m_blinkOnTimer(plat, time_on),
m_blinkOffTimer(plat, time_off)
{
    m_plat->setPinMode(m_output_pin, PIN_OUTPUT);
}

void
Blinker::execute()
{
    if(m_blinkOffTimer.stopped() && m_blinkOnTimer.stopped())
    {
        m_blinkOnTimer.start();
    }

    if(m_blinkOnTimer.running())
    {
        if(m_blinkOnTimer.expired())
        {
            m_blinkOffTimer.start();
            m_blinkOnTimer.reset();
        }
        else
        {
            m_plat->setPin(m_output_pin, m_active_level);
        }
    }

    if(m_blinkOffTimer.running())
    {
        if(m_blinkOffTimer.expired())
        {
            m_blinkOnTimer.start();
            m_blinkOffTimer.reset();
        }
        else
        {
            m_plat->setPin(m_output_pin, !m_active_level);
        }
    }
}

void
Blinker::reset()
{
        m_blinkOnTimer.reset();
        m_blinkOffTimer.reset();
        m_plat->setPin(m_output_pin, !m_active_level);
}
