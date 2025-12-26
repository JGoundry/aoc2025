#include "utils/stringUtils.hpp"

#include <cstdint>
#include <ranges>

namespace utils {
namespace {

std::expected<std::uint64_t, std::exception> strToUInt64(const std::string& str) {
  try {
    return std::stoull(str);
  } catch (const std::exception& e) {
    return std::unexpected(e);
  }
}

}  // namespace

std::ostream& operator<<(std::ostream& os, const Range& r) {
  os << "Range( " << r.lower << " - " << r.upper << " )";
  return os;
}

std::string trimWhitespace(const std::string_view& sv) {
  const auto isWhitespace = [](const unsigned char c) -> bool {
    return std::isspace(c);
  };

  auto withoutLeadingWhitespace = sv | std::views::drop_while(isWhitespace);
  auto reversed = withoutLeadingWhitespace | std::views::reverse;
  auto reversedWithoutLeadingWhitespace =
      reversed | std::views::drop_while(isWhitespace);
  auto trimmed = reversedWithoutLeadingWhitespace | std::views::reverse;

  return std::string(trimmed.begin(), trimmed.end());
}

std::expected<Range, std::string> parseRange(const std::string_view& range) {
  const auto& seperatorIdx = range.find('-');
  if (seperatorIdx == std::string::npos) {
    return std::unexpected(std::format("Invalid range: {}", range));
  }

  const auto& lower = strToUInt64(std::string(range.begin(), seperatorIdx));
  const auto& upper =
      strToUInt64(std::string(range.begin() + seperatorIdx + 1, range.end()));

  if (!lower || !upper) {
    return std::unexpected(std::format("Invalid range: {} ", range));
  }

  return Range{*lower, *upper};
}

}  // namespace utils
