#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "totalAccessiblePaper.hpp"

namespace day4 {
namespace testing {
namespace {

struct TotalAccessiblePaperTestParams {
  std::vector<std::string> grid;
  std::uint64_t expected;
};

class Day4 : public ::testing::TestWithParam<TotalAccessiblePaperTestParams> {};

}  // namespace

TEST_P(Day4, TotalAccessiblePaper) {
  const auto& data = GetParam();
  EXPECT_EQ(+data.expected,
            +totalAccessiblePaper(data.grid));  // '+' int promition hack
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    , Day4,
    ::testing::Values(TotalAccessiblePaperTestParams{{{"..@@.@@@@."},
                                                      {"@@@.@.@.@@"},
                                                      {"@@@@@.@.@@"},
                                                      {"@.@@@@..@."},
                                                      {"@@.@@@@.@@"},
                                                      {".@@@@@@@.@"},
                                                      {".@.@.@.@@@"},
                                                      {"@.@@@.@@@@"},
                                                      {".@@@@@@@@."},
                                                      {"@.@.@@@.@."}},
                                                     43},
                      TotalAccessiblePaperTestParams{{{"..."},
                                                      {".@."},
                                                      {"..."}},
                                                     1}));
// clang-format on

}  // namespace testing
}  // namespace day4
