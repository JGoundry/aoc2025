#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "solveHomework.hpp"

namespace day6 {
namespace testing {
namespace {

struct Day6TestParams {
  std::vector<std::string> homework;
  std::uint64_t expected;
};

class Day6 : public ::testing::TestWithParam<Day6TestParams> {};

}  // namespace

TEST_P(Day6, SolveHomework) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, solveHomework(data.homework));
}

INSTANTIATE_TEST_SUITE_P(, Day6,
                         ::testing::Values(Day6TestParams{
                             {"123 328  51 64",
                             " 45 64  387 23",
                              "  6 98  215 314",
                              "*   +   *   +"},
                             3263827}));

}  // namespace testing
}  // namespace day6
