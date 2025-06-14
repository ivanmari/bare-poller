// SPDX-License-Identifier: MIT
// Copyright (c) 2025 the BarePoller authors
// This file is part of BarePoller, licensed under the MIT License. See LICENSE file for details.

// This is an example of a non-blocking code using BarePoller library.
// It blinks an LED at different freq using a debounced push button



#include <BarePoller.h>

// Define the LED pin
const int LED_PIN = LED_BUILTIN; // Or any other digital pin

const int BUTTON = 4; // Or any other digital pin

// Define blinking periods (in microseconds for PrecisionTimer)
const long TIME_ON_US = 500000;  // 0.5 seconds
const long TIME_OFF_US = 500000; // 0.5 seconds

// Declare global objects
ArduinoPlat platform; // Create the platform object
Blinker slowLedBlinker(&platform, LED_PIN, TIME_ON_US, TIME_OFF_US, HIGH);
Blinker fastLedBlinker(&platform, LED_PIN, TIME_ON_US/2, TIME_OFF_US/2, HIGH);
Switch sw(&platform, BUTTON, HIGH);

void setup() {
  // Pin mode for LED_PIN is set by the Blinker constructor
  // via platform.setPinMode()
  Serial.begin(9600); // Optional: for debugging
  Serial.println("SimpleBlinker example started!");
}

void loop() {
  // Execute the blinker logic
  // This needs to be called repeatedly in the main loop
  if(sw.isOn())
  {
    slowLedBlinker.execute();
  }
  else {
    fastLedBlinker.execute();
  }

  // You can add other non-blocking code here
}
