// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef ARDUINOPLAT_H
#define ARDUINOPLAT_H

#include "Platform.h"
#include <Arduino.h> // Ensure Arduino.h is included

class ArduinoPlat : public Platform
{
public:
    ArduinoPlat();
    virtual ~ArduinoPlat();
    virtual unsigned getSystemUpTimeMinutes(); // Removed as Arduino provides only millis/micros directly
    virtual unsigned long getSystemUpTimeMillis();
    virtual unsigned long getSystemUpTimeMicros();
    virtual void setPinMode(int pin, PinMode mode);
    virtual void setPin(int pin, bool level);
    virtual bool getPin(int pin);
    virtual int  readAnalogPin(int pin);
    virtual long map(long x, long in_min, long in_max, long out_min, long out_max);
};
#endif // ARDUINOPLAT_H
