#pragma once

#include <cmath>
#include <cstdint>
#include <span>
#include <string>

namespace day8 {

struct Point {
  std::uint64_t x, y, z;
  auto operator<=>(const Point& rhs) const = default;
  friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

constexpr double euclideanDistance(const Point& a, const Point& b) {
  const double dx = static_cast<double>(b.x) - a.x;
  const double dy = static_cast<double>(b.y) - a.y;
  const double dz = static_cast<double>(b.z) - a.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::uint64_t largestCircuitsProduct(std::span<const std::string> coordinates,
                                     std::uint64_t totalConnections);

}  // namespace day8
