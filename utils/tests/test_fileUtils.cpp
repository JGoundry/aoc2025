#include "utils/stringUtils.hpp"

#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <array>

namespace utils {
namespace testing {
namespace {

struct TrimWhitespaceTestData {
  std::string_view input;
  std::string_view expected;
};

constexpr std::array data{
    TrimWhitespaceTestData{"", ""},
    TrimWhitespaceTestData{"   ", ""},
    TrimWhitespaceTestData{"test", "test"},
    TrimWhitespaceTestData{"test  ", "test"},
    TrimWhitespaceTestData{"  test", "test"},
    TrimWhitespaceTestData{"  test  ", "test"},
    TrimWhitespaceTestData{"test this", "test this"},
    TrimWhitespaceTestData{"   test    this    ", "test    this"},
};

class TrimWhitespaceTest
    : public ::testing::TestWithParam<TrimWhitespaceTestData> {};

} // namespace

TEST_P(TrimWhitespaceTest, TrimWhitespace) {
    const TrimWhitespaceTestData& testData = GetParam();
    const std::string result = trimWhitespace(testData.input);
    EXPECT_EQ(result, testData.expected);
}

INSTANTIATE_TEST_SUITE_P(, TrimWhitespaceTest, ::testing::ValuesIn(data));

} // namespace testing
} // namespace utils
