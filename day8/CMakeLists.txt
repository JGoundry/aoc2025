# Logic
add_library(day8_logic STATIC src/largestCircuitsProduct.cpp)
target_include_directories(day8_logic PUBLIC src)

# Main
add_executable(day8 src/main.cpp)
target_link_libraries(day8 PRIVATE utils day8_logic)

# Test
add_executable(test_day8 tests/test_largestCircuitsProduct.cpp)
target_link_libraries(test_day8 PRIVATE day8_logic GTest::gtest GTest::gtest_main)

# Add to ctest
gtest_discover_tests(test_day8)
