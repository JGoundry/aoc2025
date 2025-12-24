#include "totalAccessiblePaper.hpp"

namespace day4 {
namespace {

constexpr std::uint64_t paperLimit = 4;
constexpr char paperRoll = '@';
constexpr char nonPaper = '.';

bool accessibleSpot(const std::vector<std::string>& grid, std::int64_t row,
                    std::int64_t col) {
  if (row < 0 || row >= grid.size()) return true;
  if (col < 0 || col >= grid[row].size()) return true;

  return grid[row][col] != paperRoll;
}

}  // namespace

std::uint64_t totalAccessiblePaper(std::vector<std::string> grid) {
  std::uint64_t accessiblePaper{};

  bool gridUpdated{};

  do {
    gridUpdated = false;
    for (size_t row = 0; row < grid.size(); ++row) {
      for (size_t col = 0; col < grid[row].size(); ++col) {
        if (grid[row][col] != paperRoll) continue;

        std::uint64_t openSpots{};

        openSpots += accessibleSpot(grid, row - 1, col - 1);  // top left
        openSpots += accessibleSpot(grid, row - 1, col);      // top
        openSpots += accessibleSpot(grid, row - 1, col + 1);  // top right

        openSpots += accessibleSpot(grid, row, col - 1);  // left
        openSpots += accessibleSpot(grid, row, col + 1);  // right

        openSpots += accessibleSpot(grid, row + 1, col - 1);  // bottom left
        openSpots += accessibleSpot(grid, row + 1, col);      // bottom
        openSpots += accessibleSpot(grid, row + 1, col + 1);  // bottom right

        if (openSpots > paperLimit) {
          ++accessiblePaper;
          gridUpdated = true;
          grid[row][col] = nonPaper;
        }
      }
    }
  } while (gridUpdated);

  return accessiblePaper;
}

}  // namespace day4
