
#include <cstdint>
#include <iostream>
#include <print>

#include "largestCircuitsProduct.hpp"
#include "utils/fileUtils.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::println(std::cerr, "Usage: {} <input_file> <connections>", argv[0]);
    return -1;
  }

  // Validate
  const std::string_view connectionsStr = argv[2];
  std::uint64_t connections{};
  try {
     connections = std::stoull(std::string(connectionsStr));
  } catch (const std::exception& e) {
    std::println(std::cerr, "Caught exception '{}' while trying to convert connections '{}' to number.", e.what(), argv[2]);
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

  const auto ans = day8::largestCircuitsProduct(*coordinates, connections);

  std::println("Largest circuits product: {}", ans);

  return 0;
}
