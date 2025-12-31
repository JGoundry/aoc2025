#include "largestCircuitsProduct.hpp"

#include <cstdint>
#include <iostream>
#include <ranges>
#include <string>

namespace day8 {

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << "," << p.y << "," << p.z << ")";
    return os;
}

std::uint64_t largestCircuitsProduct(
    const std::vector<std::string>& coordinates) {
  auto strToPoint = [](const std::string& str) -> Point {
    try {
      auto&& xyz =
          str | std::views::split(',') |
          std::views::transform([](std::ranges::range auto&& strRange) {
            return std::stoull(std::string(std::string_view(strRange)));
          });
      return {*xyz.begin(), *std::next(xyz.begin(), 1),
              *std::next(xyz.begin(), 2)};
    } catch (...) {
      return {};
    }
  };

  // Parse points (range adaptor: transform -> convert to vector)
  const auto& points = coordinates | std::views::transform(strToPoint) |
                       std::ranges::to<std::vector>();

  return {};
}

}  // namespace day8
