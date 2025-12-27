#include "totalFreshIngredients.hpp"

#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <string>

#include "utils/stringUtils.hpp"

namespace day5 {

std::uint64_t totalFreshIngredients(const std::vector<std::string>& database) {
  const auto parseRangeReportErr = [](const auto& str) -> utils::Range {
    const auto range = utils::parseRange(str);
    if (!range) {
      std::println(std::cerr, "{}", range.error());
    }
    return range.value_or({});
  };

  auto freshRanges = database | std::views::transform(parseRangeReportErr) |
                     std::ranges::to<std::vector>();

  std::ranges::sort(freshRanges);

  std::uint64_t totalFresh{};
  std::uint64_t maxId{};

  std::ranges::for_each(
      freshRanges, [&maxId, &totalFresh](const utils::Range& r) {
        totalFresh +=
            r.upper > maxId ? r.upper + 1 - std::max(maxId + 1, r.lower) : 0;
        maxId = std::max(maxId, r.upper);
      });

  return totalFresh;
}

}  // namespace day5
