#include "splitBeams.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <set>

namespace day7 {

std::set<std::pair<size_t, size_t>> split(
    std::vector<std::string>& diagram, size_t beamRow, size_t beamCol) {
  if (beamRow >= diagram.size() || beamCol >= diagram[beamRow].size())
    return {};

  const char c = diagram[beamRow][beamCol];
  
  if (c == 'x') // seen
    return {};

  diagram[beamRow][beamCol] = 'x';

  if (c == '^') {
    std::set splitLocations = {std::pair{beamRow, beamCol}};
    splitLocations.insert_range(split(diagram, beamRow + 1, beamCol - 1));
    splitLocations.insert_range(split(diagram, beamRow + 1, beamCol + 1));
    return splitLocations;
  }

  return split(diagram, beamRow + 1, beamCol);
}

std::uint64_t splitBeams(const std::vector<std::string>& diagram) {
  if (diagram.size() < 2) return {};

  const auto startIt = std::ranges::find(diagram.front(), 'S');
  if (startIt == diagram.front().end()) return {};
  const auto startCol = std::distance(diagram.front().begin(), startIt);


  auto diagramCopy = diagram;
  auto splitLocationSet = split(diagramCopy, 1, startCol);

  return splitLocationSet.size();
}

}  // namespace day7
