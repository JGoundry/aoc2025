#include <iostream>
#include <print>

#include "largestSquareArea.hpp"
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
  const auto& coordinates = utils::readLines(*file);
  if (!coordinates) {
    std::cerr << coordinates.error() << '\n';
    return -1;
  }

  const auto ans = day9::largestSquareArea(*coordinates);

  std::println("Largest square area: {}", ans);

  return 0;
}
