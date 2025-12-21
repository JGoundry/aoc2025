#include "sumInvalidIDs.hpp"

#include "utils/fileUtils.hpp"

#include <fstream>
#include <iostream>
#include <print>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::println(std::cerr, "Usage: {} <input_file>", argv[0]);
    return -1;
  }

  // Validate filepath and open file
  const std::string_view filename = argv[1];
  std::ifstream file = utils::validateAndOpenFile(filename);
  
  // Read lines from file
  const std::expected<std::string, std::string> ranges = utils::read(file);
  if (!ranges) {
      std::println(std::cerr, "{}", ranges.error());
      return -1;
  }

  const size_t invalidSum = day2::sumInvalidIDs(*ranges);

  std::println("Invalid IDs sum: {}", invalidSum);

  return 0;
}
