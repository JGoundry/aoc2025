#include "totalFreshIngredients.hpp"

#include <algorithm>
#include <exception>
#include <expected>
#include <iostream>
#include <string>

#include "utils/stringUtils.hpp"

namespace day5 {

std::uint64_t totalFreshIngredients(const std::vector<std::string>& database) {
  std::vector<utils::Range> freshRanges;

  std::uint64_t totalFresh{};

  bool processingAvaliableIngredients{};
  for (const auto& entry : database) {
    if (entry.empty()) {
      processingAvaliableIngredients = true;
      continue;
    }

    // Process range
    if (!processingAvaliableIngredients) {
      const auto range = utils::parseRange(entry);
      if (!range) {
        std::println(std::cerr, "{}", range.error());
        continue;
      }
      freshRanges.emplace_back(*range);
      continue;
    }

    // Process ingredient
    try {
      auto ingredientID = std::stoll(entry);

      totalFresh += std::ranges::any_of(freshRanges, [ingredientID](const auto& freshRange) {
        return ingredientID >= freshRange.lower &&
               ingredientID <= freshRange.upper;
      });
    } catch (...) {
      std::println(std::cerr, "Invalid ID: {}", entry);
    }
  }

  return totalFresh;
}

}  // namespace day5
