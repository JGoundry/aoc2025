#include "totalTimelines.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <map>

namespace day7 {
namespace {

using TimelineCountMap = std::map<std::pair<size_t, size_t>, size_t>;

std::uint64_t split(TimelineCountMap& memo,
                    const std::vector<std::string>& diagram, size_t beamRow,
                    size_t beamCol) {
  if (beamRow >= diagram.size() || beamCol >= diagram[beamRow].size())
    return {};

  auto timelineCountIt = memo.find({beamRow, beamCol});
  if (timelineCountIt != memo.end()) {
    return timelineCountIt->second;
  }

  if (diagram[beamRow][beamCol] == '^') {
    std::uint64_t total{1};
    total += split(memo, diagram, beamRow + 1, beamCol - 1);
    total += split(memo, diagram, beamRow + 1, beamCol + 1);
    memo[{beamRow, beamCol}] = total;
    return total;
  }

  return split(memo, diagram, beamRow + 1, beamCol);
}

}

std::uint64_t totalTimelines(const std::vector<std::string>& diagram) {
  if (diagram.size() < 2) return {};
  const auto startIt = std::ranges::find(diagram.front(), 'S');
  if (startIt == diagram.front().end()) return {};
  const auto startCol = std::distance(diagram.front().begin(), startIt);

  TimelineCountMap map;
  const auto totalTimelines =
      split(map, diagram, 1, startCol) + 1 /* +1 for starting timeline */;

  return totalTimelines;
}

}  // namespace day7
