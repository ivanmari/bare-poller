cmake_minimum_required(VERSION 3.10)

project(BareMetalPollerTests)

# Include the Google Test framework
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Include source files from the parent directory
include_directories(../src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define the test executable
add_executable(
  run_tests
  test_switch.cpp
  test_precision_timer.cpp
  test_blinker.cpp
  ../src/Switch.cpp
  ../src/PrecisionTimer.cpp
  ../src/Blinker.cpp
  ../src/X86Platform.cpp
)

# Link the test executable against Google Test
target_link_libraries(
  run_tests
  gmock_main
)

# Enable testing
enable_testing()

# Add the test to CTest
add_test(
  NAME BareMetalPollerTests
  COMMAND run_tests
)