#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "maxJoltage.hpp"

namespace day3 {
namespace testing {
namespace {

struct MaxJoltageTestParams {
  std::vector<std::string> batteryBanks;
  std::uint64_t expected;
};

class Day3Part1 : public ::testing::TestWithParam<MaxJoltageTestParams> {};
class Day3Part2 : public ::testing::TestWithParam<MaxJoltageTestParams> {};

}  // namespace

TEST_P(Day3Part1, MaxJoltage) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, maxJoltage(data.batteryBanks, 2));
}

TEST_P(Day3Part2, MaxJoltage) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, maxJoltage(data.batteryBanks, 12));
}

// TEST_P(MaxJoltageTest, Day3Part2) {
//   const auto& data = GetParam();
//   EXPECT_EQ(data.expected, maxJoltage(data.batteryBanks, 12));
// }

INSTANTIATE_TEST_SUITE_P(
    , Day3Part1,
    ::testing::Values(MaxJoltageTestParams{{"3", "0", "0"}, 0},  // too small
                      MaxJoltageTestParams{{"30528"}, 58},
                      MaxJoltageTestParams{{"20532", "23591", "239", "891250"},
                                           278},
                      MaxJoltageTestParams{{"3945234"}, 95},
                      MaxJoltageTestParams{{
                                               {"987654321111111"},
                                               {"811111111111119"},
                                               {"234234234234278"},
                                               {"818181911112111"},
                                           },
                                           357}));

INSTANTIATE_TEST_SUITE_P(, Day3Part2,
                         ::testing::Values(MaxJoltageTestParams{
                             {
                                 {"987654321111111"},
                                 {"811111111111119"},
                                 {"234234234234278"},
                                 {"818181911112111"},
                             },
                             3121910778619}));

}  // namespace testing
}  // namespace day3
