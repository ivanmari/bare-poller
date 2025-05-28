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
#ifndef BLINKER_H
#define BLINKER_H

#include "PrecisionTimer.h"
// Switch.h will be included by BarePoller.h or directly by user sketch if needed
// #include "Switch.h" 
#include "Platform.h" // Added Platform.h include

class Blinker
{
public:
    Blinker(Platform* plat, int output_pin, long int time_on, long int time_off, bool active_level);

    void execute();
    void reset();

private:
    Platform* m_plat;
    PrecisionTimer m_blinkOffTimer;
    PrecisionTimer m_blinkOnTimer;
    const int m_output_pin;
    const bool m_active_level;
};
#endif //BLINKER_H
