#pragma once

#include <cstdint>
#include <expected>
#include <ostream>
#include <string>
#include <string_view>

namespace utils {

struct Range {
  std::int64_t lower;
  std::int64_t upper;

  friend std::ostream& operator<<(std::ostream& os, const Range& r);
};

std::string trimWhitespace(const std::string_view& sv);

std::expected<Range, std::string> parseRange(const std::string_view& range);

}  // namespace utils
