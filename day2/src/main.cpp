#include <expected>
#include <iostream>
#include <print>

#include "sumInvalidIDs.hpp"
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
  const auto ranges = utils::read(*file);
  if (!ranges) {
    std::cerr << ranges.error() << '\n';
    return -1;
  }

  const size_t invalidSum = day2::sumInvalidIDs(*ranges);

  std::println("Invalid IDs sum: {}", invalidSum);

  return 0;
}
