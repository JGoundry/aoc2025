cmake_minimum_required(VERSION 3.31)
project(day1 CXX) # set project name and [language]

# fetch gtest using FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# C++ standard
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS        FALSE)

# Misc
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Safe cracking lib (logic)
add_library(safe_cracking src/safeCracking.cpp)

# Create main executable and link logic lib
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE safe_cracking)

# Create test executable link logic lib and gtest
add_executable(tests src/test_safeCracking.cpp)
target_link_libraries(tests PRIVATE safe_cracking GTest::gtest_main)

# Include headers
target_include_directories(safe_cracking PUBLIC src)

# Enable CTest
enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)
