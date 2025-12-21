#include <gtest/gtest.h>

#include "crackSafe.hpp"

namespace day1 {
namespace testing {
namespace {

struct CrackSafeTestData {
  const std::vector<std::string> safeOps;
  const size_t expected;
};

const CrackSafeTestData data{
    .safeOps =
        std::vector<std::string>{
            "L68",
            "L30",
            "R48",
            "L5",
            "R60",
            "L55",
            "L1",
            "L99",
            "R14",
            "L82",
        },
    .expected = 6,
};

}  // namespace

TEST(Day1, CrackSafe) {
  auto result = crackSafe(data.safeOps);
  EXPECT_EQ(data.expected, result);
}

}  // namespace testing
}  // namespace day1
