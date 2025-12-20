#include "crackSafe.hpp"

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
  const std::expected<std::vector<std::string>, std::string> safeOps = utils::readLines(file);
  if (!safeOps) {
      std::println(std::cerr, "{}", safeOps.error());
      return -1;
  }

  const size_t code = day1::crackSafe(safeOps.value());

  std::println("Safe code: {}", code);

  // don't return safe code as exit values only go up to 255
  return 0;
}
