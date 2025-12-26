#pragma once

#include <cstdint>
#include <expected>
#include <ostream>
#include <string>
#include <string_view>

namespace utils {

struct Range {
  std::uint64_t lower;
  std::uint64_t upper;

  auto operator<=>(const Range& other) const = default;

  friend std::ostream& operator<<(std::ostream& os, const Range& r);
};

std::string trimWhitespace(const std::string_view& sv);

std::expected<Range, std::string> parseRange(const std::string_view& range);

}  // namespace utils
