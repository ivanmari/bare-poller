// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef PLATFORM_H
#define PLATFORM_H

enum PinMode
{
    PIN_INPUT,
    PIN_OUTPUT
};

class Platform
{
public:
    virtual unsigned long getSystemUpTimeMicros() = 0;
    virtual unsigned long getSystemUpTimeMillis() = 0;
    virtual unsigned getSystemUpTimeMinutes() = 0;
    virtual void setPinMode(int pin, PinMode mode) = 0;
    virtual void setPin(int pin, bool level) = 0;
    virtual bool getPin(int pin) = 0;
    virtual int readAnalogPin(int pin) = 0;
    virtual long map(long x, long in_min, long in_max, long out_min, long out_max) = 0;
};
#endif // PLATFORM_H
