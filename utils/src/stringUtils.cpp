#include "utils/stringUtils.hpp"

#include <ranges>

namespace utils {

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

}  // namespace utils
