#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Blinker.h"
#include "Platform.h"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;

class MockPlatformForBlinker : public Platform {
public:
    MOCK_METHOD(void, setPinMode, (int pin, PinMode mode), (override));
    MOCK_METHOD(void, setPin, (int pin, bool level), (override));
    MOCK_METHOD(unsigned long, getSystemUpTimeMicros, (), (override));

    // Provide implementations for other pure virtual methods
    bool getPin(int pin) override { return false; }
    unsigned getSystemUpTimeMinutes() override { return 0; }
    unsigned long getSystemUpTimeMillis() override { return getSystemUpTimeMicros() / 1000; }
    int readAnalogPin(int pin) override { return 0; }
    long map(long x, long in_min, long in_max, long out_min, long out_max) override { return 0; }
};

TEST(BlinkerTest, InitialState) {
    MockPlatformForBlinker platform;
    int pin = 3;
    long on_time_us = 10000;
    long off_time_us = 20000;
    bool active_level = true;

    EXPECT_CALL(platform, setPinMode(pin, PIN_OUTPUT));
    Blinker blinker(&platform, pin, on_time_us, off_time_us, active_level);
}

TEST(BlinkerTest, BlinkingCycle) {
    InSequence s;
    MockPlatformForBlinker platform;
    int pin = 3;
    long on_time_us = 10000;
    long off_time_us = 20000;
    bool active_level = true;

    EXPECT_CALL(platform, setPinMode(pin, PIN_OUTPUT));
    Blinker blinker(&platform, pin, on_time_us, off_time_us, active_level);

    // First execute: initial state, starts ON timer, sets pin to active
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000));
    EXPECT_CALL(platform, setPin(pin, active_level));
    blinker.execute();

    // Second execute: ON timer running, not expired, pin stays active
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + on_time_us - 1));
    EXPECT_CALL(platform, setPin(pin, active_level));
    blinker.execute();

    // Third execute: ON timer expires, starts OFF timer, sets pin to inactive
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + on_time_us)); // for expired()
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + on_time_us)); // for start()
    EXPECT_CALL(platform, setPin(pin, !active_level));
    blinker.execute();

    // Fourth execute: OFF timer running, not expired, pin stays inactive
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + on_time_us + off_time_us - 1));
    EXPECT_CALL(platform, setPin(pin, !active_level));
    blinker.execute();

    // Fifth execute: OFF timer expires, starts ON timer again, sets pin to active
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + on_time_us + off_time_us)); // for expired()
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + on_time_us + off_time_us)); // for start()
    EXPECT_CALL(platform, setPin(pin, active_level));
    blinker.execute();
}

TEST(BlinkerTest, Reset) {
    MockPlatformForBlinker platform;
    int pin = 3;
    long on_time_us = 10000;
    long off_time_us = 20000;
    bool active_level = true;

    EXPECT_CALL(platform, setPinMode(pin, PIN_OUTPUT));
    Blinker blinker(&platform, pin, on_time_us, off_time_us, active_level);

    // Start the cycle
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000));
    EXPECT_CALL(platform, setPin(pin, active_level));
    blinker.execute();

    // Reset the blinker
    EXPECT_CALL(platform, setPin(pin, !active_level));
    blinker.reset();

    // After reset, it should start the on-cycle again
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(150000));
    EXPECT_CALL(platform, setPin(pin, active_level));
    blinker.execute();
}