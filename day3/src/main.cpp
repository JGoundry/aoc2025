#include <cstdint>
#include <iostream>
#include <print>

#include "maxJoltage.hpp"
#include "utils/fileUtils.hpp"

namespace {

// part1 = 2, part2 = 12
constexpr std::uint8_t requestedBatteries = 12;

}

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
  const auto batteryBanks = utils::readLines(*file);
  if (!batteryBanks) {
    std::cerr << batteryBanks.error() << '\n';
    return -1;
  }

  // Get max jolts
  const auto maxJoltage = day3::maxJoltage(*batteryBanks, requestedBatteries);

  std::println("Max joltage: {}", maxJoltage);

  return 0;
}
