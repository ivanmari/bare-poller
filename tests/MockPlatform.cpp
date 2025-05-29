// tests/MockPlatform.cpp
#include "MockPlatform.h"

MockPlatform::MockPlatform() : m_currentTimeMicros(0), m_currentTimeMillis(0) {}

void MockPlatform::setCurrentTimeMicros(unsigned long time_us) {
    m_currentTimeMicros = time_us;
    // Optionally update millis too, assuming 1ms = 1000us
    m_currentTimeMillis = m_currentTimeMicros / 1000;
}

void MockPlatform::advanceTimeMicros(unsigned long duration_us) {
    m_currentTimeMicros += duration_us;
    m_currentTimeMillis = m_currentTimeMicros / 1000;
}

void MockPlatform::advanceTimeMillis(unsigned long duration_ms) {
    m_currentTimeMillis += duration_ms;
    m_currentTimeMicros = m_currentTimeMillis * 1000;
}

unsigned long MockPlatform::getSystemUpTimeMicros() {
    return m_currentTimeMicros;
}

unsigned long MockPlatform::getSystemUpTimeMillis() {
    // Return explicitly tracked millis or derive from micros
    return m_currentTimeMicros / 1000; // Or m_currentTimeMillis if advanced separately
}

unsigned MockPlatform::getSystemUpTimeMinutes() {
    return m_currentTimeMicros / 60000000UL; // Or m_currentTimeMillis / 60000
}

// --- Stubs for other methods ---
void MockPlatform::setPinMode(int pin, PinMode mode) {
    // No-op or log call
    // Example: pin_events.push_back({pin, mode, false});
}

void MockPlatform::setPin(int pin, bool level) {
    // No-op or log call
}

bool MockPlatform::getPin(int pin) {
    return false; // Default value
}

int MockPlatform::readAnalogPin(int pin) {
    return 0; // Default value
}

long MockPlatform::map(long x, long in_min, long in_max, long out_min, long out_max) {
    // Basic map implementation if needed, or just return x or 0
    if (in_max == in_min) return out_min; // Avoid division by zero
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
