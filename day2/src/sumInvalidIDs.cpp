#include "sumInvalidIDs.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "utils/stringUtils.hpp"

namespace day2 {
namespace {

const bool debug = std::getenv("AOC_DEBUG");

#define DEBUG_PRINT(msg) \
  if (debug) std::cout << msg << '\n'

std::vector<utils::Range> parseRanges(const std::string_view& rangesStr) {
  std::vector<utils::Range> out;

  for (const auto& rangeView : rangesStr | std::views::split(',')) {
    const std::string_view rangeStr(rangeView.begin(), rangeView.size());

    auto range = utils::parseRange({rangeView.begin(), rangeView.end()});
    if (!range) {
      std::println(std::cerr, "{}", range.error());
    }

    out.emplace_back(std::move(*range));
    DEBUG_PRINT(" - " << out.back());
  }

  return out;
}

std::vector<std::uint64_t> gatherInvalidIDs(const utils::Range& range) {
  std::vector<std::uint64_t> invalidIDs;

  for (auto id{range.lower}; id <= range.upper; ++id) {
    const std::string idStr = std::to_string(id);

    const size_t idLen = idStr.size();
    const size_t maxSequenceLen = idStr.size() / 2;

    // Loop through the possible sequence lengths
    for (size_t sequenceLen = 1; sequenceLen <= maxSequenceLen; ++sequenceLen) {
      // Check this is a valid sequence length
      if (idLen % sequenceLen != 0) continue;

      // Get first sequence
      size_t l = 0;
      size_t r = sequenceLen;
      const std::string_view firstSequence(idStr.begin() + l,
                                           idStr.begin() + r);

      bool invalidID{};

      // Iterate through rest, if all identical, we have an invalid ID
      do {
        l += sequenceLen;
        r += sequenceLen;

        const std::string_view nextSequence(idStr.begin() + l,
                                            idStr.begin() + r);

        // Valid ID check
        if (nextSequence != firstSequence) {
          break;
        }

        // We have hit the end of the sequence, ID must be invalid
        if (r == idLen) {
          invalidID = true;
        }
      } while (r < idLen);

      if (invalidID) {
        invalidIDs.push_back(id);
        DEBUG_PRINT("Invalid ID: " << id);
        break;
      }
    }
  }

  return invalidIDs;
}

}  // namespace

std::uint64_t sumInvalidIDs(const std::string_view& rangesStr) {
  DEBUG_PRINT("Input: " << rangesStr);

  const std::vector<utils::Range> ranges = parseRanges(rangesStr);

  // Use parallel unsequence (SIMD) execution policy to gather invalid IDs
  const auto sum = std::transform_reduce(
      std::execution::par_unseq, ranges.begin(), ranges.end(), std::uint64_t{},
      std::plus{}, [](const utils::Range r) {
        std::uint64_t internalSum{};
        for (const std::uint64_t invalidID : gatherInvalidIDs(r)) {
          internalSum += invalidID;
        }
        return internalSum;
      });

  DEBUG_PRINT("Invalid IDs sum: " << sum);

  return sum;
}

}  // namespace day2
