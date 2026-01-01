#include "largestSquareArea.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <vector>

namespace day9 {
namespace {

struct Point {
  std::uint64_t x;
  std::uint64_t y;

  friend std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
  }
};

struct Rect {
  Point a;
  Point b;

  const std::uint64_t width() const {
    // Warning: narrowing conversion
    const std::int64_t diff = a.x - b.x + 1;
    return std::abs(diff);
  }
  const std::uint64_t height() const {
    // Warning: narrowing conversion
    const std::int64_t diff = a.y - b.y + 1;
    return std::abs(diff);
  }

  const std::uint64_t area() const {
    return width() * height();
  }

  friend std::ostream& operator<<(std::ostream& os, const Rect& r) {
    os << "(" << r.a << "," << r.b << ")";
    return os;
  }
};

}  // namespace

std::uint64_t largestSquareArea(
    const std::span<const std::string> coordinates) {
  // Point parsing function
  auto strToPoint = [](const std::string& str) -> Point {
    try {
      auto&& xyz =
          str | std::views::split(',') |
          std::views::transform([](std::ranges::range auto&& strRange) {
            return std::stoull(std::string(std::string_view(strRange)));
          });

      // Safely get the x,y coordinates from the range
      auto it = xyz.begin();
      const auto end = xyz.end();
      if (it == end) return {};
      const auto x = *it++;
      if (it == end) return {};
      const auto y = *it++;

      return {x, y};
    } catch (...) {
      return {};
    }
  };

  auto points = coordinates | std::views::transform(strToPoint);
  const auto nPoints = points.size();

  std::vector<Rect> allRectanges;
  allRectanges.reserve(nPoints * (nPoints - 1) / 2);

  for (auto i{0}; i < nPoints; ++i) {
    for (auto j{i + 1}; j < nPoints; ++j) {
      allRectanges.emplace_back(Rect{points[i], points[j]});
    }
  }

  if (allRectanges.empty()) return {};

  std::ranges::nth_element(allRectanges, allRectanges.begin(),
                                            std::greater<>{}, &Rect::area);


  return allRectanges.front().area();
}

}  // namespace day9
