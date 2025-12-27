# Logic
add_library(day6_logic STATIC src/solveHomework.cpp)
target_include_directories(day6_logic PUBLIC src)

# Main

# Test
add_executable(test_day6 tests/test_solveHomework.cpp)
target_link_libraries(test_day6 PRIVATE day6_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day6)
