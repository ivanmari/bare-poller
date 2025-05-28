// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

#ifndef BAREPOLLER_H
#define BAREPOLLER_H

// Ensure Arduino specific types are available first
#include <Arduino.h>

// Include the abstract Platform definition first
#include "Platform.h"

// Include the concrete Arduino platform implementation
#include "ArduinoPlat.h"

// Core library classes that depend on Platform
#include "PrecisionTimer.h"
#include "Switch.h"
#include "Blinker.h"

#endif // BAREPOLLER_H
