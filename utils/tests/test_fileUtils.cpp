#include <gtest/gtest.h>

#include <ios>

#include "utils/fileUtils.hpp"

namespace utils {
namespace testing {

TEST(OpenFile, EmptyPath) {
  const auto file = openFile("", std::ios_base::in);
  EXPECT_FALSE(file);
}

TEST(ReadLines, EmptyStream) {
  std::ifstream file;
  const auto result = readLines(file);
  EXPECT_FALSE(result);
}

}  // namespace testing
}  // namespace utils
