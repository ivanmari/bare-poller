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
// Include the main library header
#include <BarePoller.h>

// Define the LED pin
const int LED_PIN = LED_BUILTIN; // Or any other digital pin

// Define blinking periods (in microseconds for PrecisionTimer)
const long TIME_ON_US = 500000;  // 0.5 seconds
const long TIME_OFF_US = 500000; // 0.5 seconds

// Declare global objects
ArduinoPlat platform; // Create the platform object
Blinker ledBlinker(&platform, LED_PIN, TIME_ON_US, TIME_OFF_US, HIGH); // Create the Blinker object

void setup() {
  // Pin mode for LED_PIN is set by the Blinker constructor
  // via platform.setPinMode()
  Serial.begin(9600); // Optional: for debugging
  Serial.println("SimpleBlinker example started!");
}

void loop() {
  // Execute the blinker logic
  // This needs to be called repeatedly in the main loop
  ledBlinker.execute();

  // You can add other non-blocking code here
}
