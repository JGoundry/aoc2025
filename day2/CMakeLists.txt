# Logic lib
add_library(day2_logic STATIC src/sumInvalidIDs.cpp)
target_include_directories(day2_logic PUBLIC src)
target_link_libraries(day2_logic PRIVATE utils)

# Main executable
add_executable(day2 src/main.cpp)
target_link_libraries(day2 PRIVATE utils day2_logic)

# Test executable
add_executable(test_day2 tests/test_sumInvalidIDs.cpp)
target_link_libraries(test_day2 PRIVATE day2_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day2)
