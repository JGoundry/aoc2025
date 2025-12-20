# Crack safe lib (logic)
add_library(day1_logic STATIC src/crackSafe.cpp)
target_include_directories(day1_logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create main executable and link logic lib
add_executable(day1 src/main.cpp)
target_link_libraries(day1 PRIVATE utils day1_logic)

# Create test executable link logic lib and gtest
add_executable(test_day1 src/test_crackSafe.cpp)
target_link_libraries(test_day1 PRIVATE day1_logic GTest::gtest_main)

# Let ctest discover gtests
gtest_discover_tests(test_day1)
