#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "maxJoltage.hpp"

namespace day3 {
namespace testing {
namespace {

struct MaxJoltageTestData {
  std::vector<std::string> batteryBanks;
  std::uint64_t expected;
};

class MaxJoltageTest : public ::testing::TestWithParam<MaxJoltageTestData> {};

}  // namespace

TEST_P(MaxJoltageTest, Day3) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, maxJoltage(data.batteryBanks));
}

INSTANTIATE_TEST_SUITE_P(
    , MaxJoltageTest,
    ::testing::Values(MaxJoltageTestData{{"3", "0", "0"}, 3},
                      MaxJoltageTestData{{"30528"}, 58},
                      MaxJoltageTestData{
                          {"20532", "1", "23591", "239", "891250"}, 279},
                      MaxJoltageTestData{{"3945234"}, 95},
                      MaxJoltageTestData{{
                                             {"987654321111111"},
                                             {"811111111111119"},
                                             {"234234234234278"},
                                             {"818181911112111"},
                                         },
                                         357}));

}  // namespace testing
}  // namespace day3
