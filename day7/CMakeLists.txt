# Logic
add_library(day7_logic STATIC src/splitBeams.cpp)
target_include_directories(day7_logic PUBLIC src)

# Main
add_executable(day7 src/main.cpp)
target_link_libraries(day7 PRIVATE utils day7_logic)

# Test
add_executable(test_day7 tests/test_splitBeams.cpp)
target_link_libraries(test_day7 PRIVATE day7_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day7)
