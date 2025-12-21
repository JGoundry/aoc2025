#include "sumInvalidIDs.hpp"

#include <cstdint>
#include <gtest/gtest.h>

#include <string_view>

namespace day2 {
namespace testing {

struct SumInvalidIDsTestData {
  std::string_view ranges;
  std::uint64_t expected;
};

constexpr SumInvalidIDsTestData data{
    .ranges = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
              "1698522-1698528,446443-446449,38593856-38593862,565653-565659,"
              "824824821-824824827,2121212118-2121212124",
    .expected = 4174379265,
};

TEST(SumInvalidIDs, TestData) {
  const std::uint64_t result = sumInvalidIDs(data.ranges);
  EXPECT_EQ(result, data.expected);
}

} // namespace testing
} // namespace day2
