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
