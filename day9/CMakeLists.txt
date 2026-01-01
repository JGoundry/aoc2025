# Logic
add_library(day9_logic STATIC src/largestSquareArea.cpp)
target_include_directories(day9_logic PUBLIC src)

# Main
add_executable(day9 src/main.cpp)
target_link_libraries(day9 PRIVATE utils day9_logic)

# Test
add_executable(test_day9 tests/test_largestSquareArea.cpp)
target_link_libraries(test_day9 PRIVATE day9_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day9)
