// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#include "ArduinoPlat.h"

long
ArduinoPlat::map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return ::map(x, in_min, in_max, out_min, out_max);
}

unsigned
ArduinoPlat::getSystemUpTimeMinutes()
{
    return ::millis()/60000;
}

unsigned long
ArduinoPlat::getSystemUpTimeMillis()
{
    return millis();
}

unsigned long
ArduinoPlat::getSystemUpTimeMicros()
{
    return micros();
}

void
ArduinoPlat::setPinMode(int pin, PinMode mode)
{
    switch(mode)
    {
    case PIN_INPUT:
        ::pinMode(pin, INPUT);
        break;
    case PIN_OUTPUT:
        ::pinMode(pin, OUTPUT);
        break;
    }
}

void
ArduinoPlat::setPin(int pin, bool level)
{
    ::digitalWrite (pin, level ? HIGH : LOW);
}

bool
ArduinoPlat::getPin(int pin)
{
    return ::digitalRead (pin);
}

int
ArduinoPlat::readAnalogPin(int pin)
{
    return ::analogRead(pin);
}
