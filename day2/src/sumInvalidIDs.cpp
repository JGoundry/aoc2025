#include "sumInvalidIDs.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <expected>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace day2 {
namespace {

const bool debug = std::getenv("AOC_DEBUG");

#define DEBUG_PRINT(msg) \
  if (debug) std::cout << msg << '\n'

struct Range {
  std::uint64_t lower;
  std::uint64_t upper;

  friend std::ostream& operator<<(std::ostream& os, const Range& r) {
    os << "Range( " << r.lower << " - " << r.upper << " )";
    return os;
  }
};

std::expected<std::uint64_t, std::exception> strToInt(const std::string& str) {
  try {
    return std::stoll(str);
  } catch (const std::exception& e) {
    return std::unexpected(e);
  }
}

std::vector<Range> parseRanges(const std::string_view& rangesStr) {
  std::vector<Range> out;

  for (const auto& rangeView : rangesStr | std::views::split(',')) {
    const std::string_view rangeStr(rangeView.begin(), rangeView.size());

    const auto& seperatorIdx = rangeStr.find('-');
    if (seperatorIdx == std::string::npos) {
      std::println(std::cerr, "Invalid range: ", rangeStr);
      continue;
    }

    const auto& lower = strToInt(std::string(rangeView.begin(), seperatorIdx));
    const auto& upper = strToInt(
        std::string(rangeView.begin() + seperatorIdx + 1, rangeView.end()));
    if (!lower || !upper) {
      std::println(std::cerr, "Invalid range: ", rangeStr);
    }

    out.emplace_back(Range{*lower, *upper});
    DEBUG_PRINT(" - " << out.back());
  }

  return out;
}

std::vector<std::uint64_t> gatherInvalidIDs(const Range& range) {
  std::vector<std::uint64_t> invalidIDs;

  for (size_t id{range.lower}; id <= range.upper; ++id) {
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

  const std::vector<Range> ranges = parseRanges(rangesStr);

  std::uint64_t sum{};
  for (const Range& range : ranges) {
    for (const std::uint64_t invalidID : gatherInvalidIDs(range)) {
      sum += invalidID;
    }
  }

  DEBUG_PRINT("Invalid IDs sum: " << sum);

  return sum;
}

}  // namespace day2
