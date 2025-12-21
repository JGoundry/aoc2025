#include <gtest/gtest.h>

#include "utils/fileUtils.hpp"

namespace utils {
namespace testing {

TEST(ValidateAndOpenFile, EmptyPath) {
  const std::ifstream file = validateAndOpenFile("");
  EXPECT_FALSE(file.is_open());
}

TEST(ReadLines, EmptyStream) {
  std::ifstream file;
  const auto result = readLines(file);
  EXPECT_FALSE(result.has_value());
}

}  // namespace testing
}  // namespace utils
