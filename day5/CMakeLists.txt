# Logic
add_library(day5_logic STATIC src/totalFreshIngredients.cpp)
target_include_directories(day5_logic PUBLIC src)
target_link_libraries(day5_logic PRIVATE utils)

# Main
add_executable(day5 src/main.cpp)
target_link_libraries(day5 PRIVATE utils day5_logic)

# Tests
add_executable(test_day5 tests/test_totalFreshIngredients.cpp)
target_link_libraries(test_day5 PRIVATE day5_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day5)
