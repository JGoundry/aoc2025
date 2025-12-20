# Logic lib
add_library(day2_logic STATIC src/addInvalidIDs.cpp)
target_include_directories(day2_logic PUBLIC src)

# Main executable

# Test executable
add_executable(test_day2 tests/test_addInvalidIDs.cpp)
target_link_libraries(test_day2 PRIVATE day2_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day2)
