#include <cstdint>
#include <expected>
#include <iostream>
#include <print>

#include "crackSafe.hpp"
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
  const auto safeOps = utils::readLines(*file);
  if (!safeOps) {
    std::cerr << safeOps.error() << '\n';
    return -1;
  }

  const std::uint64_t code = day1::crackSafe(safeOps.value());

  std::println("Safe code: {}", code);

  // don't return safe code as exit values only go up to 255
  return 0;
}
