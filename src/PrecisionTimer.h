// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef PRECISIONTIMER_H
#define PRECISIONTIMER_H

#include "Platform.h"

class PrecisionTimer
{
public:
    PrecisionTimer(Platform* plat, unsigned long timeout);

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
