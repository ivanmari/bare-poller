// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BareMetalPoller authors
// This file is part of BareMetalPoller, licensed under the MIT License. See LICENSE file for details.

#ifndef BAREMETALPOLLER_H
#define BAREMETALPOLLER_H

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

#endif // BAREMETALPOLLER_H
