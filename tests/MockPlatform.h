// tests/MockPlatform.h
#ifndef MOCK_PLATFORM_H
#define MOCK_PLATFORM_H

#include "../src/Platform.h" // Assuming Platform.h is in src/
#include <vector> // For logging calls if desired

// Forward declaration if PrecisionTimer methods use other Platform features extensively
// For now, we only strictly need to mock time functions for PrecisionTimer

class MockPlatform : public Platform {
public:
    MockPlatform();

    // Time control methods
    void setCurrentTimeMicros(unsigned long time_us);
    void advanceTimeMicros(unsigned long duration_us);
    void advanceTimeMillis(unsigned long duration_ms);


    // Platform interface implementation
    unsigned long getSystemUpTimeMicros() override;
    unsigned long getSystemUpTimeMillis() override;
    unsigned getSystemUpTimeMinutes() override; // Can be derived or separately controlled

    // Stubs for other Platform methods (not strictly needed by PrecisionTimer's core logic)
    void setPinMode(int pin, PinMode mode) override;
    void setPin(int pin, bool level) override;
    bool getPin(int pin) override;
    int readAnalogPin(int pin) override;
    long map(long x, long in_min, long in_max, long out_min, long out_max) override;

    // Optional: Struct to log pin changes or other calls for more complex tests
    // struct PinEvent { int pin; PinMode mode; bool level; /* other relevant data */ };
    // std::vector<PinEvent> pin_events;

private:
    unsigned long m_currentTimeMicros;
    unsigned long m_currentTimeMillis; // If tracking separately, or derive from micros
};

#endif // MOCK_PLATFORM_H
