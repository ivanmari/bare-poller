#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "PrecisionTimer.h"
#include "Platform.h"

using ::testing::Return;

class MockPlatformForTimer : public Platform {
public:
    MOCK_METHOD(unsigned long, getSystemUpTimeMicros, (), (override));

    // Provide implementations for other pure virtual methods
    void setPinMode(int pin, PinMode mode) override {}
    bool getPin(int pin) override { return false; }
    unsigned getSystemUpTimeMinutes() override { return 0; }
    unsigned long getSystemUpTimeMillis() override { return getSystemUpTimeMicros() / 1000; }
    void setPin(int pin, bool level) override {}
    int readAnalogPin(int pin) override { return 0; }
    long map(long x, long in_min, long in_max, long out_min, long out_max) override { return 0; }
};

TEST(PrecisionTimerTest, IsStoppedInitially) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    ASSERT_TRUE(timer.stopped());
    ASSERT_FALSE(timer.running());
    ASSERT_FALSE(timer.expired());
}

TEST(PrecisionTimerTest, StartsAndRuns) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    ASSERT_TRUE(timer.running());
    ASSERT_FALSE(timer.stopped());
}

TEST(PrecisionTimerTest, StopsAfterBeingStarted) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(8000));
    timer.stop();
    ASSERT_TRUE(timer.stopped());
    ASSERT_FALSE(timer.running());
}

TEST(PrecisionTimerTest, ResetsAfterBeingStarted) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    timer.reset();
    ASSERT_TRUE(timer.stopped());
    ASSERT_FALSE(timer.running());
}

TEST(PrecisionTimerTest, ExpiresAfterTimeout) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000 + timeout));
    ASSERT_TRUE(timer.expired());
}

TEST(PrecisionTimerTest, NotExpiredBeforeTimeout) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000 + timeout - 1));
    ASSERT_FALSE(timer.expired());
}

TEST(PrecisionTimerTest, RemainingTime) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(8000));
    ASSERT_EQ(timer.remaining(), timeout - 3000);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000 + timeout));
    ASSERT_EQ(timer.remaining(), 0);
}

TEST(PrecisionTimerTest, RemainingTimeAfterExpiry) {
    MockPlatformForTimer platform;
    unsigned long timeout = 10000;
    PrecisionTimer timer(&platform, timeout);

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000));
    timer.start();

    EXPECT_CALL(platform, getSystemUpTimeMicros()).WillOnce(Return(5000 + timeout + 2000));
    ASSERT_EQ(timer.remaining(), 0);
}