#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "totalTimelines.hpp"

namespace day7 {
namespace testing {
namespace {

struct Day7TestParams {
  std::vector<std::string> diagram;
  std::uint64_t expected;
};

class Day7 : public ::testing::TestWithParam<Day7TestParams> {};

}  // namespace

TEST_P(Day7, TotalTimelines) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, totalTimelines(data.diagram));
}

INSTANTIATE_TEST_SUITE_P(, Day7,
                         ::testing::Values(Day7TestParams{{{".......S......."},
                                                           {"..............."},
                                                           {".......^......."},
                                                           {"..............."},
                                                           {"......^.^......"},
                                                           {"..............."},
                                                           {".....^.^.^....."},
                                                           {"..............."},
                                                           {"....^.^...^...."},
                                                           {"..............."},
                                                           {"...^.^...^.^..."},
                                                           {"..............."},
                                                           {"..^...^.....^.."},
                                                           {"..............."},
                                                           {".^.^.^.^.^...^."},
                                                           {"..............."}},
                                                          40}));

}  // namespace testing
}  // namespace day7
