#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace day8 {

struct Position {
  std::uint64_t x, y, z;
  auto operator<=>(const Position& rhs) const = default;
};

constexpr double euclideanDistance(const Position& a, const Position& b) {
  const double dx = static_cast<double>(b.x) - a.x;
  const double dy = static_cast<double>(b.y) - a.y;
  const double dz = static_cast<double>(b.z) - a.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::uint64_t largestCircuitsProduct(
    const std::vector<std::string>& coordinates);

}  // namespace day8
