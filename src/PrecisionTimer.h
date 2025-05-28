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
#ifndef PRECISIONTIMER_H
#define PRECISIONTIMER_H

#include "Platform.h"

class PrecisionTimer
{
public:
    PrecisionTimer(Platform* plat, unsigned long timeout);
    virtual ~PrecisionTimer();

    virtual void stop();
    virtual void start();
    virtual void reset();

    virtual bool running() const;
    virtual bool stopped() const;
    virtual bool expired() const;
    virtual long remaining() const;

protected:

private:
    Platform*  m_plat;
    unsigned long m_timeStart;
    unsigned long m_timeElapsed;
    unsigned long m_timeout;
    bool m_active;
};
#endif // PRECISIONTIMER_H
