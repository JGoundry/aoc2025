# Logic lib
add_library(day3_logic STATIC src/maxJoltage.cpp)
target_include_directories(day3_logic PUBLIC src)

# Main executable
add_executable(day3 src/main.cpp)
target_link_libraries(day3 PRIVATE utils day3_logic)

# Test executable
add_executable(test_day3 tests/test_maxJoltage.cpp)
target_link_libraries(test_day3 PRIVATE day3_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day3)
