#include "maxJoltage.hpp"

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <execution>
#include <iostream>
#include <iterator>
#include <string>

namespace day3 {
namespace {

const bool debug = std::getenv("AOC_DEBUG");
#define DEBUG_PRINT(msg) \
  if (debug) std::cout << msg << '\n';

std::uint8_t charToInt(const char c) {
  if (c < '0' || c > '9') return 0;
  return c - '0';
}

std::uint8_t maxJoltage(const std::string& batteryBank) {
  DEBUG_PRINT("Proccessing battery bank: " << batteryBank);

  if (batteryBank.empty()) {
    DEBUG_PRINT(" - Empty, returning 0")
    return 0;
  }

  if (batteryBank.size() == 1) {
    DEBUG_PRINT(" - Sizeof 1, returning only battery")
    return charToInt(batteryBank[0]);
  }

  std::uint64_t l = batteryBank.size() - 2;
  std::uint64_t r = batteryBank.size() - 1;

  DEBUG_PRINT("Starting batteries: " << batteryBank[l] << " "
                                     << batteryBank[r]);

  // iterate over battery bank backwards and update l or r if we see a bigger
  // battery
  for (auto it = batteryBank.rbegin() + 2; it != batteryBank.rend();
       std::advance(it, 1)) {
    // update if battery bigger than current left
    if (*it >= batteryBank[l]) {
      DEBUG_PRINT("- New largest battery for l: " << *it);

      const auto oldBattery = l;

      // update left battery index
      l = std::distance(batteryBank.begin(), std::prev(it.base(), 1));

      // update right battery if old left was bigger
      if (batteryBank[oldBattery] >= batteryBank[r]) {
        DEBUG_PRINT("- New largest battery for r: " << batteryBank[oldBattery]);
        r = oldBattery;
      }
    }
  }

  DEBUG_PRINT("Final largest batteries: " << batteryBank[l] << " "
                                          << batteryBank[r]);

  try {
    return std::stoi(std::string{batteryBank[l], batteryBank[r]});
  } catch (const std::exception& e) {
    DEBUG_PRINT("Caught exception converting battery stoi: " << e.what());
    return 0;
  }
}

}  // namespace

std::uint64_t maxJoltage(const std::vector<std::string>& batteryBanks) {
  const auto sum = std::transform_reduce(
      std::execution::par_unseq, batteryBanks.begin(), batteryBanks.end(),
      std::uint64_t{}, std::plus{},
      static_cast<std::uint8_t (*)(const std::string&)>(maxJoltage));

  return sum;
}

}  // namespace day3
