#include <gtest/gtest.h>

#include <cstdint>

#include "gtest/gtest.h"
#include "largestCircuitsProduct.hpp"

namespace day8 {
namespace testing {
namespace {

struct Day8TestParams {
  std::vector<std::string> coordinates;
  std::uint64_t expected;
};

class Day8 : public ::testing::TestWithParam<Day8TestParams> {};

}  // namespace

TEST(EuclideanDistance3D, Test) {
  EXPECT_DOUBLE_EQ(316.90219311326956,
                   euclideanDistance({162, 817, 812}, {425, 690, 689}));
}

TEST_P(Day8, LargestCircuitsProduct) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, largestCircuitsProduct(data.coordinates));
}

INSTANTIATE_TEST_SUITE_P(
    , Day8,
    ::testing::Values(Day8TestParams{
        {{"162,817,812"}, {"57,618,57"},   {"906,360,560"}, {"592,479,940"},
         {"352,342,300"}, {"466,668,158"}, {"542,29,236"},  {"431,825,988"},
         {"739,650,466"}, {"52,470,668"},  {"216,146,977"}, {"819,987,18"},
         {"117,168,530"}, {"805,96,715"},  {"346,949,466"}, {"970,615,88"},
         {"941,993,340"}, {"862,61,35"},   {"984,92,344"},  {"425,690,689"}},
        40}));

}  // namespace testing
}  // namespace day8
