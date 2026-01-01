#include "largestCircuitsProduct.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <ranges>
#include <set>
#include <string>

namespace day8 {
namespace {

class PointCombination {
 public:
  PointCombination(const Point& a, const Point& b) {
    // Assign so smallest point is 'a', combination rather than permutation
    if (a < b) {
      a_ = a;
      b_ = b;
    } else {
      a_ = b;
      b_ = a;
    }
    distance_ = euclideanDistance(a_, b_);
  }

  std::uint64_t distance() const { return distance_; }
  Point a() const { return a_; }
  Point b() const { return b_; }

  auto operator<=>(const PointCombination& rhs) const = default;

  friend std::ostream& operator<<(std::ostream& os,
                                  const PointCombination& pc) {
    os << "distance: " << pc.distance_ << ", a: " << pc.a_ << ", b: " << pc.b_;
    return os;
  }

 private:
  std::uint64_t distance_;
  Point a_;
  Point b_;
};

class Circuit {
 public:
  Circuit(std::initializer_list<Point> points) : points_{points} {}

  bool contains(const Point& p) const { return points_.contains(p); }
  size_t size() const { return points_.size(); }

  void insert(const Point& p) { points_.insert(p); }
  void merge(const Circuit& other) { points_.insert_range(other.points_); }

 private:
  std::set<Point> points_;
};

}  // namespace

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << "," << p.y << "," << p.z << ")";
  return os;
}

std::uint64_t largestCircuitsProduct(const std::span<const std::string> coordinates,
                                     std::uint64_t totalConnections) {
  if (coordinates.empty() || totalConnections == 0) return {};

  // Point parsing function
  auto strToPoint = [](const std::string& str) -> Point {
    try {
      auto&& xyz =
          str | std::views::split(',') |
          std::views::transform([](std::ranges::range auto&& strRange) {
            return std::stoull(std::string(std::string_view(strRange)));
          });

      // Safely get the x,y,z coordinates from the range
      auto it = xyz.begin();
      const auto end = xyz.end();
      if (it == end) return {};
      const auto x = *it++;
      if (it == end) return {};
      const auto y = *it++;
      if (it == end) return {};
      const auto z = *it++;

      return {x, y, z};
    } catch (...) {
      return {};
    }
  };

  // Parse points (range adaptor: transform -> convert to vector)
  const auto& points = coordinates | std::views::transform(strToPoint);
  const auto nPoints = points.size();

  // Get all possible point combinations including their distance
  std::vector<PointCombination> allPointCombinations;
  allPointCombinations.reserve(nPoints * (nPoints - 1) / 2);
  for (auto i{0}; i < nPoints; ++i) {
    for (auto j{i + 1}; j < nPoints; ++j) {
      allPointCombinations.emplace_back(PointCombination(points[i], points[j]));
    }
  }

  // Sort the point combinations so that the n smallest distances are first
  totalConnections = std::min(totalConnections, allPointCombinations.size());
  std::ranges::partial_sort(
      allPointCombinations,
      std::next(allPointCombinations.begin(), totalConnections), {},
      &PointCombination::distance);

  // Create circuits by connecting n points with the smallest distance
  std::vector<Circuit> circuits;
  for (const auto& pc :
       allPointCombinations | std::views::take(totalConnections)) {
    // Get circuits which points already belong to if there is any
    std::vector<Circuit>::iterator aCircuit{circuits.end()};
    std::vector<Circuit>::iterator bCircuit{circuits.end()};
    for (auto it = circuits.begin(); it != circuits.end();
         std::advance(it, 1)) {
      if (it->contains(pc.a())) {
        aCircuit = it;
      }
      if (it->contains(pc.b())) {
        bCircuit = it;
      }
      if (aCircuit != circuits.end() && bCircuit != circuits.end()) break;
    }

    // If neither is in circuit, create new circuit
    if (aCircuit == circuits.end() && bCircuit == circuits.end()) {
      circuits.emplace_back(Circuit{pc.a(), pc.b()});
    }
    // If a is in circuit but b is not. Add b to aCircuit
    else if (aCircuit != circuits.end() && bCircuit == circuits.end()) {
      aCircuit->insert(pc.b());
    }
    // If b is in circuit but a is not. Add a to bCircuit
    else if (aCircuit == circuits.end() && bCircuit != circuits.end()) {
      bCircuit->insert(pc.a());
    }
    // If both are in circuits, and circuits are different. Merge and delete one
    else if (aCircuit != bCircuit) {
      aCircuit->merge(*bCircuit);
      circuits.erase(bCircuit);
    }
  }
  if (circuits.empty()) return {};

  // Create our own end iterator as we only want the 3 largest circuits
  const auto endIt =
      std::next(circuits.begin(), std::min(3UL, circuits.size()));

  // Sort so we get the largest 3 first by size
  std::ranges::partial_sort(circuits, endIt, std::greater<>{}, &Circuit::size);

  // Sum the 3 largest circuit sizes
  return std::transform_reduce(circuits.begin(), endIt, std::uint64_t{1},
                               std::multiplies<>{},
                               [](const Circuit& c) { return c.size(); });
}

}  // namespace day8
