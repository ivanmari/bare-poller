// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef X86PLATFORM_H
#define X86PLATFORM_H

#ifdef X86_PLAT
#include "../Platform.h"


class X86Platform : public Platform
{
    public:
        X86Platform();
        virtual ~X86Platform();

    virtual unsigned getSystemUpTimeMinutes();
    virtual unsigned long getSystemUpTimeMillis();
    virtual unsigned long getSystemUpTimeMicros();
    virtual void setPinMode(int pin, PinMode mode);
    virtual void setPin(int pin, bool level);
    virtual bool getPin(int pin);
    virtual void delay(unsigned millis);
    virtual int  readAnalogPin(int pin);
    virtual long map(long x, long in_min, long in_max, long out_min, long out_max);

};

#endif // X86_PLAT
#endif // X86PLATFORM_H
