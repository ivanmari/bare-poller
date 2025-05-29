// tests/TestPrecisionTimer.cpp
#include <cassert>
#include <limits> // For std::numeric_limits
#include <iostream> // For printing test names

#include "../src/PrecisionTimer.h" // Adjust path if necessary
#include "MockPlatform.h"    // Adjust path if necessary

// Helper to print test names
void printTestName(const char* name) {
    std::cout << "Running test: " << name << "..." << std::endl;
}

void testTimerExpiresCorrectly() {
    printTestName("testTimerExpiresCorrectly");
    MockPlatform platform;
    unsigned long timeout = 1000; // 1000 microseconds
    PrecisionTimer timer(&platform, timeout);

    platform.setCurrentTimeMicros(0);
    timer.start();
    assert(timer.running());
    assert(!timer.stopped());
    assert(!timer.expired());

    platform.advanceTimeMicros(timeout - 1);
    assert(!timer.expired());

    platform.advanceTimeMicros(1); // Exactly at timeout
    assert(timer.expired());
    assert(timer.running()); // Expired() doesn't change active state
    assert(!timer.stopped());  // Expired() doesn't change active state
}

void testRemainingTime() {
    printTestName("testRemainingTime");
    MockPlatform platform;
    unsigned long timeout = 2000;
    PrecisionTimer timer(&platform, timeout);

    platform.setCurrentTimeMicros(0);
    timer.start();
    assert(timer.remaining() == (long)timeout);

    platform.advanceTimeMicros(500);
    assert(timer.remaining() == (long)(timeout - 500));

    platform.advanceTimeMicros(timeout - 500); // Advance to full timeout
    assert(timer.expired());
    assert(timer.remaining() == 0);

    // Test remaining after expiry
    platform.advanceTimeMicros(100); // Advance past timeout
    assert(timer.expired());
    assert(timer.remaining() == 0);
}

void testStopTimer() {
    printTestName("testStopTimer");
    MockPlatform platform;
    unsigned long timeout = 1000;
    PrecisionTimer timer(&platform, timeout);

    platform.setCurrentTimeMicros(0);
    timer.start();

    platform.advanceTimeMicros(500);
    assert(!timer.expired());
    timer.stop();

    assert(timer.stopped());
    assert(!timer.running());
    assert(!timer.expired()); // Not expired because it was stopped
    assert(timer.remaining() == (long)(timeout - 500)); // Remaining reflects the state when stopped

    platform.advanceTimeMicros(1000); // Advance time well past original timeout
    assert(!timer.expired()); // Still not expired as it's stopped
    assert(timer.remaining() == (long)(timeout - 500));

    // Restarting the timer
    timer.start(); // Resumes from where it left off in terms of m_timeElapsed
    assert(timer.running());
    platform.advanceTimeMicros(timeout - 500 - 1); // Advance just before final expiry
    assert(!timer.expired());
    assert(timer.remaining() > 0);

    platform.advanceTimeMicros(1); // Advance to final expiry
    assert(timer.expired());
    assert(timer.remaining() == 0);
}

void testResetTimer() {
    printTestName("testResetTimer");
    MockPlatform platform;
    unsigned long timeout = 1000;
    PrecisionTimer timer(&platform, timeout);

    platform.setCurrentTimeMicros(0);
    timer.start();
    platform.advanceTimeMicros(500);
    timer.stop(); // m_timeElapsed is 500

    timer.reset();
    assert(timer.stopped());
    assert(!timer.running());
    assert(!timer.expired());
    // Remaining time for a reset timer could be argued:
    // 1. Full timeout because m_timeElapsed is 0 (current code for remaining() when inactive uses m_timeElapsed)
    // 2. 0 if reset means it's fully 'done' until started.
    // The current remaining() for inactive timer: timeout - m_timeElapsed. Since reset zeroes m_timeElapsed, it's full timeout.
    assert(timer.remaining() == (long)timeout);


    timer.start(); // Fresh start
    platform.setCurrentTimeMicros(1000); // Set current time to something new
    timer.reset(); // Reset while running
    platform.setCurrentTimeMicros(0); // Reset platform time for consistency in test
    timer.start(); // Start fresh from time 0
    assert(timer.running());
    assert(timer.remaining() == (long)timeout);
    platform.advanceTimeMicros(timeout);
    assert(timer.expired());
}

const unsigned long ULONG_MAX_VAL = std::numeric_limits<unsigned long>::max();

void testExpiredWrapAround() {
    printTestName("testExpiredWrapAround");
    MockPlatform platform;
    unsigned long timeout = 200;
    // Timer starts 100us before wrap, timeout is 200us, so should expire 100us after wrap.
    platform.setCurrentTimeMicros(ULONG_MAX_VAL - 100);
    PrecisionTimer timer(&platform, timeout);
    timer.start();

    assert(!timer.expired()); // Not yet wrapped, not expired

    // Advance time to 50us after wrap (total 150us elapsed)
    // Current time becomes (ULONG_MAX_VAL - 100) + 150.
    // If ULONG_MAX_VAL - 100 + 150 wraps, new micros is 150 - 100 - 1 = 49 (this is how unsigned math works)
    // So, advance such that current micros becomes 49.
    // Amount to advance = 150
    platform.advanceTimeMicros(150); // Current time is now effectively 49
    assert(!timer.expired()); // Should be 150us elapsed, timeout is 200us

    platform.advanceTimeMicros(50); // Advance another 50us. Total 200us elapsed. Current time is 99.
    assert(timer.expired());
    assert(timer.remaining() == 0);
}

void testExpiredSaturation() {
    printTestName("testExpiredSaturation");
    MockPlatform platform;
    
    // Test scenario:
    // Timer with timeout=ULONG_MAX_VAL. Start. Advance by ULONG_MAX_VAL-10. Stop. (m_timeElapsed = ULONG_MAX_VAL-10)
    // Start again. Advance by 20. (current_active_elapsed = 20)
    // Sum (m_timeElapsed + current_active_elapsed) would be (ULONG_MAX_VAL-10) + 20 = ULONG_MAX_VAL+10.
    // This sum should saturate to ULONG_MAX_VAL, not wrap to 9.
    // expired() check: ULONG_MAX_VAL >= ULONG_MAX_VAL. True.
    // remaining() check: should be 0.
    
    platform.setCurrentTimeMicros(0);
    PrecisionTimer sat_timer(&platform, ULONG_MAX_VAL); // Timeout is MAX
    
    sat_timer.start();
    platform.advanceTimeMicros(ULONG_MAX_VAL - 10); // Elapse most of the time
    assert(!sat_timer.expired());
    sat_timer.stop(); // m_timeElapsed is now ULONG_MAX_VAL - 10

    // At this point, platform time is ULONG_MAX_VAL - 10.
    // When we start again, m_timeStart will be ULONG_MAX_VAL - 10.
    sat_timer.start(); 
    
    // Advance time by 5 microseconds.
    // current_micros becomes (ULONG_MAX_VAL - 10) + 5 = ULONG_MAX_VAL - 5.
    // current_active_elapsed = (ULONG_MAX_VAL - 5) - (ULONG_MAX_VAL - 10) = 5.
    platform.advanceTimeMicros(5); 
    assert(!sat_timer.expired()); // Total elapsed (ULONG_MAX_VAL-10)+5 = ULONG_MAX_VAL-5. Remaining 5.
    assert(sat_timer.remaining() == 5);

    // Advance time by another 10 microseconds.
    // current_micros becomes (ULONG_MAX_VAL - 5) + 10. This wraps to 4.
    // current_active_elapsed (since last start) = 5 + 10 = 15.
    // total_effective_elapsed = (m_timeElapsed from stop: ULONG_MAX_VAL - 10) + (current_active_elapsed: 15).
    // This sum is (ULONG_MAX_VAL - 10) + 15 = ULONG_MAX_VAL + 5.
    // The saturation logic should ensure this becomes ULONG_MAX_VAL.
    platform.advanceTimeMicros(10); 
                                   
    assert(sat_timer.expired());   // Check: total_effective_elapsed (saturated ULONG_MAX_VAL) >= timeout (ULONG_MAX_VAL) is true.
    assert(sat_timer.remaining() == 0); // total_elapsed >= timeout, so 0.
}


void testRemainingWrapAround() {
    printTestName("testRemainingWrapAround");
    MockPlatform platform;

    // Scenario 1: Start near wrap, query remaining after wrap
    unsigned long timeout1 = 300;
    platform.setCurrentTimeMicros(ULONG_MAX_VAL - 100); // Start 100us before wrap
    PrecisionTimer timer1(&platform, timeout1);
    timer1.start();

    assert(timer1.remaining() == 300);

    platform.advanceTimeMicros(150); // Advance 150us. Current time is effectively 49 (wrapped).
                                     // Elapsed = 150us.
    assert(timer1.remaining() == (long)(timeout1 - 150)); // 300 - 150 = 150

    platform.advanceTimeMicros(150); // Advance another 150us. Total 300us elapsed.
    assert(timer1.expired());
    assert(timer1.remaining() == 0);

    // Scenario 2: Test the m_timeStart + m_timeout overflow case from original remaining() bug
    // Old faulty logic: remaining_time = m_timeStart + m_timeout - current_micros;
    // New logic in PrecisionTimer: remaining_time = m_timeout - total_elapsed;
    // Test case: m_timeStart = ULONG_MAX_VAL - 1000. m_timeout = 2000. current_micros advanced by 500.
    // Expected remaining: 1500.
    // Old logic would be: ( (ULONG_MAX_VAL - 1000 + 2000) % (ULONG_MAX_VAL+1) ) - (ULONG_MAX_VAL - 1000 + 500)
    // which is (999) - (ULONG_MAX_VAL - 500) -> large negative.
    // New logic calculation:
    //   elapsed_in_current_run = ((ULONG_MAX_VAL - 1000 + 500) % (ULONG_MAX_VAL+1)) - (ULONG_MAX_VAL - 1000) = 500.
    //   current_total_elapsed = 0 (m_timeElapsed) + 500 = 500.
    //   500 < 2000 is true.
    //   returns (long)(2000 - 500) = 1500.

    unsigned long timeout2 = 2000;
    platform.setCurrentTimeMicros(ULONG_MAX_VAL - 1000); // Set current time for m_timeStart
    PrecisionTimer timer2(&platform, timeout2);
    timer2.start(); // m_timeStart is ULONG_MAX_VAL - 1000

    platform.advanceTimeMicros(500); // current time is ULONG_MAX_VAL - 500. Elapsed since start is 500.
    assert(timer2.remaining() == (long)(timeout2 - 500)); // Expected: 2000 - 500 = 1500. This asserts the fix.
}

void testStopStartWrapAround() {
    printTestName("testStopStartWrapAround");
    MockPlatform platform;
    unsigned long timeout = 500;
    platform.setCurrentTimeMicros(ULONG_MAX_VAL - 100); // Start 100us before wrap
    PrecisionTimer timer(&platform, timeout);
    timer.start(); // m_timeStart = ULONG_MAX_VAL - 100

    platform.advanceTimeMicros(150); // Advance 150us. current_micros is effectively 49.
                                     // Elapsed = 150us.
    timer.stop(); // m_timeElapsed should be 150.
                  
    assert(timer.stopped());
    assert(timer.remaining() == (long)(timeout - 150)); // 500 - 150 = 350

    // platform time is 49 (from ULONG_MAX_VAL - 100 + 150)
    timer.start(); // m_timeStart is 49. m_timeElapsed (carried over) is 150.
    assert(timer.running());
    // When started, remaining considers m_timeElapsed and current_active_elapsed (which is 0 at start)
    // remaining = timeout - (m_timeElapsed + 0) = 500 - 150 = 350
    assert(timer.remaining() == (long)(timeout - 150)); 

    platform.advanceTimeMicros(100); // current_micros is 49 + 100 = 149. Elapsed this run is 100.
                                     // Total elapsed = 150 (from m_timeElapsed) + 100 (this run) = 250.
    assert(!timer.expired());
    assert(timer.remaining() == (long)(timeout - 250)); // 500 - 250 = 250

    platform.advanceTimeMicros(250); // current_micros is 149+250 = 399. Elapsed this run is 100+250=350.
                                     // Total elapsed = 150 (from m_timeElapsed) + 350 (this run) = 500.
    assert(timer.expired());
    assert(timer.remaining() == 0);
}

// It would be good to have a main function to run these tests if not using a framework
// For now, these functions are defined. A separate step might involve creating a test runner.
// Example main (optional for this subtask, can be added in step 4):
// Add these function calls to the main() if it's being used.
// Example main additions (optional for this subtask):

int main() {
    printTestName("Starting PrecisionTimer Tests");

    testTimerExpiresCorrectly();
    testRemainingTime();
    testStopTimer();
    testResetTimer();

    testExpiredWrapAround();
    testExpiredSaturation();
    testRemainingWrapAround();
    testStopStartWrapAround();

    std::cout << "\nAll PrecisionTimer tests completed successfully!" << std::endl;
    return 0;
}
