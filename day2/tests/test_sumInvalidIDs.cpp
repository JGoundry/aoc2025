#include "sumInvalidIDs.hpp"

#include <cstdint>
#include <gtest/gtest.h>

#include <string_view>

namespace day2 {
namespace testing {

struct AddInvalidIDsTestData {
  std::string_view ranges;
  uint64_t expected;
};

constexpr AddInvalidIDsTestData data{
    .ranges = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
              "1698522-1698528,446443-446449,38593856-38593862",
    .expected = 1227775554,
};

TEST(AddInvalidIDs, TestData) {
    const uint64_t result = sumInvalidIDs(data.ranges);
    EXPECT_EQ(result, data.expected);
}

} // namespace testing
} // namespace day2
