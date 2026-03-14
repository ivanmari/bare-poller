#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Switch.h"
#include "Platform.h"

using ::testing::Return;

class MockPlatform : public Platform {
public:
    MOCK_METHOD(void, setPinMode, (int pin, PinMode mode), (override));
    MOCK_METHOD(bool, getPin, (int pin), (override));
    MOCK_METHOD(unsigned long, getSystemUpTimeMicros, (), (override));

    // Provide implementations for other pure virtual methods
    unsigned getSystemUpTimeMinutes() override { return 0; }
    unsigned long getSystemUpTimeMillis() override { return getSystemUpTimeMicros() / 1000; }
    void setPin(int pin, bool level) override {}
    int readAnalogPin(int pin) override { return 0; }
    long map(long x, long in_min, long in_max, long out_min, long out_max) override { return 0; }
};

TEST(SwitchTest, IsOffWhenInstantiated) {
    MockPlatform platform;
    int pin = 1;
    bool activeLevel = true;

    EXPECT_CALL(platform, setPinMode(pin, PIN_INPUT));

    Switch s(&platform, pin, activeLevel);

    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(!activeLevel));

    ASSERT_FALSE(s.isOn());
}

TEST(SwitchTest, IsOnAfterDebounce) {
    MockPlatform platform;
    int pin = 1;
    bool activeLevel = true;
    unsigned long debounce_us = 20000;

    EXPECT_CALL(platform, setPinMode(pin, PIN_INPUT));

    Switch s(&platform, pin, activeLevel, debounce_us);

    // Simulate pin being active
    EXPECT_CALL(platform, getPin(pin)).WillRepeatedly(Return(activeLevel));

    // First call to isOn, timer starts
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000));
    ASSERT_FALSE(s.isOn());

    // Second call, still within debounce period
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + debounce_us - 1));
    ASSERT_FALSE(s.isOn());

    // Third call, after debounce period
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000 + debounce_us));
    ASSERT_TRUE(s.isOn());
}

TEST(SwitchTest, StaysOffWithBouncing) {
    MockPlatform platform;
    int pin = 1;
    bool activeLevel = true;
    unsigned long debounce_us = 20000;

    EXPECT_CALL(platform, setPinMode(pin, PIN_INPUT));

    Switch s(&platform, pin, activeLevel, debounce_us);

    // Pin is active, timer starts
    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(activeLevel));
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(100000));
    ASSERT_FALSE(s.isOn());

    // Pin becomes inactive (bounces), timer resets
    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(!activeLevel));
    ASSERT_FALSE(s.isOn());

    // Pin is active again, timer restarts
    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(activeLevel));
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(110000));
    ASSERT_FALSE(s.isOn());

    // Time passes, but not enough to overcome debounce
    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(activeLevel));
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(110000 + debounce_us - 1));
    ASSERT_FALSE(s.isOn());

    // Finally, switch is stable and on
    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(activeLevel));
    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(110000 + debounce_us));
    ASSERT_TRUE(s.isOn());
}

TEST(SwitchTest, IsOffWhenInactive) {
    MockPlatform platform;
    int pin = 1;
    bool activeLevel = true;

    EXPECT_CALL(platform, setPinMode(pin, PIN_INPUT));

    Switch s(&platform, pin, activeLevel);

    EXPECT_CALL(platform, getPin(pin)).WillOnce(Return(!activeLevel));
    ASSERT_FALSE(s.isOn());
}