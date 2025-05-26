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
