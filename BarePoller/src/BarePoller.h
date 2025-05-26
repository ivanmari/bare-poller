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
