#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "largestSquareArea.hpp"

namespace day9 {
namespace testing {
namespace {

struct Day9TestParams {
  std::vector<std::string> coordinates;
  std::uint64_t expected;
};

class Day9 : public ::testing::TestWithParam<Day9TestParams> {};

}  // namespace

TEST_P(Day9, LargestSquareArea) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, largestSquareArea(data.coordinates));
}

INSTANTIATE_TEST_SUITE_P(, Day9,
                         ::testing::Values(Day9TestParams({{"7,1"},
                                                           {"11,1"},
                                                           {"11,7"},
                                                           {"9,7"},
                                                           {"9,5"},
                                                           {"2,5"},
                                                           {"2,3"},
                                                           {"7,3"}},
                                                          50)));

}  // namespace testing
}  // namespace day9
