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
