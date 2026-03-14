// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#include "Blinker.h"

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
    // State 1: OFF, waiting to turn ON.
    if (m_blinkOffTimer.running()) {
        if (m_blinkOffTimer.expired()) {
            m_blinkOffTimer.reset();
            m_blinkOnTimer.start();
            m_plat->setPin(m_output_pin, m_active_level);
        } else {
            m_plat->setPin(m_output_pin, !m_active_level);
        }
    }
    // State 2: ON, waiting to turn OFF.
    else if (m_blinkOnTimer.running()) {
        if (m_blinkOnTimer.expired()) {
            m_blinkOnTimer.reset();
            m_blinkOffTimer.start();
            m_plat->setPin(m_output_pin, !m_active_level);
        } else {
            m_plat->setPin(m_output_pin, m_active_level);
        }
    }
    // State 0: Initial state, start blinking.
    else {
        m_blinkOnTimer.start();
        m_plat->setPin(m_output_pin, m_active_level);
    }
}

void
Blinker::reset()
{
        m_blinkOnTimer.reset();
        m_blinkOffTimer.reset();
        m_plat->setPin(m_output_pin, !m_active_level);
}