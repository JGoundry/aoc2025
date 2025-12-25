# Logic lib
add_library(day4_logic STATIC src/totalAccessiblePaper.cpp)
target_include_directories(day4_logic PUBLIC src)

# Main
add_executable(day4 src/main.cpp)
target_link_libraries(day4 PRIVATE utils day4_logic)

# Tests
add_executable(test_day4 tests/test_totalAccessiblePaper.cpp)
target_link_libraries(test_day4 PRIVATE day4_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day4)
