#include "maxJoltage.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <execution>
#include <functional>
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

template <typename T>
void recursiveBatteryUpdate(
    const std::string& batteryBank, std::uint8_t batteryBankIdxToCheck,
    const std::ranges::subrange<T> currentLargestBatteries) {
  // Stop condition: we have no more batteries in the range to update
  if (currentLargestBatteries.empty()) return;

  // Check if new battery is bigger than what we have stored currently
  if (batteryBank[batteryBankIdxToCheck] >=
      batteryBank[currentLargestBatteries.front()]) {
    // Store old idx and update the current largest battery idx
    const auto oldIdx = currentLargestBatteries.front();
    *currentLargestBatteries.begin() = batteryBankIdxToCheck;

    // Recurse with the old largest battery and range starting from the next
    // battery we have
    recursiveBatteryUpdate(
        batteryBank, oldIdx,
        std::ranges::subrange(std::next(currentLargestBatteries.begin()),
                              currentLargestBatteries.end()));
  }
}

std::uint64_t maxJoltage(const std::string& batteryBank,
                         const std::uint8_t requestedBatteries) {
  DEBUG_PRINT("Proccessing battery bank: " << batteryBank);

  if (batteryBank.size() < requestedBatteries) {
    DEBUG_PRINT(" - Battery bank not big enough for requseted batteries: "
                << requestedBatteries);
    return 0;
  }

  if (batteryBank.size() == 1) {
    DEBUG_PRINT(" - Sizeof 1, returning only battery")
    return charToInt(batteryBank[0]);
  }

  // To solve this we will iterate over the battery bank backwards
  // We can take the last n requested and then work towards the start
  // If we see a larger battery than our first we will update it, the old
  // battery will now be the next largest avaliable so we can recurse down our
  // stored batteries and update.

  // Get the last n battery indexes
  std::vector<std::uint8_t> largestBatteryIdxs(requestedBatteries);
  std::ranges::generate(
      largestBatteryIdxs,
      [i = batteryBank.size() - requestedBatteries] mutable -> std::uint8_t {
        return i++;
      });

  // Iterate over battery bank backwards and update batteries recursively
  // whenever we see a larger battery
  for (auto batteryIdxToCheck = largestBatteryIdxs.front() - 1;
       batteryIdxToCheck >= 0; --batteryIdxToCheck) {
    recursiveBatteryUpdate(batteryBank, batteryIdxToCheck,
                           std::ranges::subrange(largestBatteryIdxs));
  }

  // Convert battery indexes to an actual number
  try {
    std::string batteries(requestedBatteries, 0);
    std::ranges::transform(largestBatteryIdxs, batteries.begin(),
                           [&](std::uint8_t idx) { return batteryBank[idx]; });
    return std::stoll(batteries);
  } catch (const std::exception& e) {
    DEBUG_PRINT("Caught exception converting battery stoll: " << e.what());
    return 0;
  }
}

}  // namespace

std::uint64_t maxJoltage(const std::vector<std::string>& batteryBanks,
                         const std::uint8_t requestedBatteries) {
  const auto sum = std::transform_reduce(
      std::execution::par_unseq, batteryBanks.begin(), batteryBanks.end(),
      std::uint64_t{}, std::plus{},
      std::bind(
          static_cast<std::uint64_t (*)(const std::string&, std::uint8_t)>(
              maxJoltage),
          std::placeholders::_1, requestedBatteries));

  return sum;
}

}  // namespace day3
