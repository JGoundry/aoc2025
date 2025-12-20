#include "utils/fileUtils.hpp"

#include <gtest/gtest.h>

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

}
}
