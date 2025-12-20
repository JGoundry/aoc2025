# Utils lib
add_library(utils STATIC src/fileUtils.cpp src/stringUtils.cpp)
target_include_directories(utils PUBLIC include)

# Test executable
add_executable(test_utils tests/test_fileUtils.cpp)
target_link_libraries(test_utils PRIVATE utils GTest::gtest_main)

# Let ctest discover gtests
gtest_discover_tests(test_utils)
