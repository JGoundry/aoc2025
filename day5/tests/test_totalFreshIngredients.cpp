#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "totalFreshIngredients.hpp"

namespace day5 {
namespace testing {
namespace {

struct TotalFreshIngredientsTestParams {
  std::vector<std::string> database;
  std::uint64_t expected;
};

class Day5 : public ::testing::TestWithParam<TotalFreshIngredientsTestParams> {
};

}  // namespace

TEST_P(Day5, TotalFreshIngredients) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, day5::totalFreshIngredients(data.database));
}

INSTANTIATE_TEST_SUITE_P(, Day5,
                         ::testing::Values(TotalFreshIngredientsTestParams{
                             {
                                 {"3-5"},
                                 {"10-14"},
                                 {"16-20"},
                                 {"12-18"},
                             },
                             14}));

}  // namespace testing
}  // namespace day5
