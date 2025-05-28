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
#include "ArduinoPlat.h"
// Arduino.h is already included in ArduinoPlat.h

ArduinoPlat::ArduinoPlat()
{
    //ctor
}

ArduinoPlat::~ArduinoPlat()
{
    //dtor
}

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
        ::pinMode(pin, INPUT); // Added :: scope specifier
        break;
    case PIN_OUTPUT:
        ::pinMode(pin, OUTPUT); // Added :: scope specifier
        break;
    }
}

void
ArduinoPlat::setPin(int pin, bool level)
{
    // Removed if (level) and else block for direct mapping
    ::digitalWrite (pin, level ? HIGH : LOW); // Added :: scope specifier
}

bool
ArduinoPlat::getPin(int pin)
{
    return ::digitalRead (pin); // Added :: scope specifier
}

int
ArduinoPlat::readAnalogPin(int pin)
{
    return ::analogRead(pin); // Added :: scope specifier
}
