#include <iostream>
#include <print>

#include "totalAccessiblePaper.hpp"
#include "utils/fileUtils.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::println(std::cerr, "Usage: {} <input_file>", argv[0]);
    return -1;
  }

  // Validate filepath and open file
  const std::string_view filename = argv[1];
  auto file = utils::openFile(filename, std::ios_base::in);
  if (!file) {
    std::cerr << file.error() << '\n';
    return -1;
  }

  // Read lines from file
  const auto& grid = utils::readLines(*file);
  if (!grid) {
    std::cerr << grid.error() << '\n';
    return -1;
  }

  const auto totalAccessiblePaper = day4::totalAccessiblePaper(std::move(*grid));

  std::println("Total accessible paper: {}", totalAccessiblePaper);

  return 0;
}
