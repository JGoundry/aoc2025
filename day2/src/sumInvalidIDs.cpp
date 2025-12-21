#include "sumInvalidIDs.hpp"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <expected>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace day2 {
namespace {

const bool debug = std::getenv("AOC_DEBUG");

#define DEBUG_PRINT(msg)                                                       \
  if (debug)                                                                   \
  std::cout << msg << '\n'

struct Range {
  uint64_t lower;
  uint64_t upper;

  friend std::ostream& operator<<(std::ostream& os, const Range& r) {
      os << "Range( " << r.lower << " - " << r.upper << " )";
      return os;
  }
};

std::expected<uint64_t, std::exception> strToInt(const std::string& str)  {
    try {
        return std::stoll(str);
    } catch (const std::exception& e) {
       return std::unexpected(e);
    }
}

std::vector<Range> parseRanges(const std::string_view &rangesStr) {
  std::vector<Range> out;

  for (const auto &rangeView : rangesStr | std::views::split(',')) {
    const std::string_view rangeStr(rangeView.begin(), rangeView.size());

    const auto& seperatorIdx = rangeStr.find('-');
    if (seperatorIdx == std::string::npos) {
        std::println(std::cerr, "Invalid range: ", rangeStr);
        continue;
    }
    
    const auto& lower = strToInt(std::string(rangeView.begin(), seperatorIdx));
    const auto& upper = strToInt(std::string(rangeView.begin() + seperatorIdx + 1, rangeView.end()));
    if (!lower || !upper) {
        std::println(std::cerr, "Invalid range: ", rangeStr);
    }

    out.emplace_back(Range{*lower, *upper});
    DEBUG_PRINT(" - " << out.back());
  }

  return out;
}

std::vector<uint64_t> gatherInvalidIDs(const Range &range) {
    std::vector<uint64_t> invalidIDs;

  for (size_t id = range.lower; id <= range.upper; ++id) {
    const std::string idStr = std::to_string(id);

    // continue if starts with 0    
    if (idStr.empty() || idStr[0] == '0')
        continue;

    // continue if odd number
    if (idStr.size() % 2 == 1)
        continue;

    // split number in half
    size_t mid = idStr.size() / 2;
    std::string_view left(idStr.begin(), idStr.begin() + mid);
    std::string_view right(idStr.begin() + mid, idStr.end());

    // if left == right, invalid
    if (left == right) {
        invalidIDs.push_back(id);
        DEBUG_PRINT("Invalid ID: " << id);
    }
  }

  return invalidIDs;
}

} // namespace

uint64_t sumInvalidIDs(const std::string_view &rangesStr) {
  DEBUG_PRINT("Input: " << rangesStr);

  const std::vector<Range> ranges = parseRanges(rangesStr);

  uint64_t sum{};
  for (const Range &range : ranges) {
    for (const uint64_t invalidID : gatherInvalidIDs(range)) {
      sum += invalidID;
    }
  }

  DEBUG_PRINT("Invalid IDs sum: " << sum);

  return sum;
}

} // namespace day2
