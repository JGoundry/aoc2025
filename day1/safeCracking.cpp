#include "safeCracking.hpp"

#include <cassert>
#include <expected>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>

constexpr bool debug = true;

#define DEBUG_PRINT(msg)                                                       \
  if constexpr (debug)                                                         \
    std::cout << msg << '\n';

std::string trimWhitespace(const std::string_view &sv) {
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

int opToInt(const std::string &str) {
  try {
    auto num = std::string(str.begin() + 1, str.end());
    return std::stoi(num);

  } catch (const std::exception &e) {
    std::cerr << "Caugh exception: " << e.what() << '\n';
    return 0;
  }
}

class SafeDial {
public:
  SafeDial() : num_(50), zeroCount_(0) {}

  SafeDial &operator+=(const std::string_view& op) {
    // precondition: 0 <= num < 100
    assert(0 <= num_ && num_ < 100);

    const std::string opTrimmed = trimWhitespace(op);

    DEBUG_PRINT(" - " << opTrimmed);

    switch (opTrimmed[0]) {
    case 'L': {
      const auto i = opToInt(opTrimmed);
      const auto newNum = (num_ - i) % -100;
      num_ = (newNum < 0 ? 100 + newNum : newNum) % 100;
      DEBUG_PRINT("    " << num_);
      break;
    }
    case 'R': {
      const auto i = opToInt(opTrimmed);
      num_ = (num_ + i) % 100;
      DEBUG_PRINT("    " << num_);
      break;
    }
    default: {
      std::cerr << "Invalid op: " << op << '\n';
      break;
    }
    }

    if (num_ == 0) {
      ++zeroCount_;
    }

    // postcondition: 0 <= num < 100
    assert(0 <= num_ && num_ < 100);

    return *this;
  }

  int dialNumber() const {
      return num_;
  }

  size_t zeroCount() const {
      return zeroCount_;
  }

  void print(std::ostream &os) const { os << *this << '\n'; }

  friend std::ostream &operator<<(std::ostream &os, const SafeDial &sd) {
    os << "Safe num:   " << sd.num_ << '\n' << "Zero count: " << sd.zeroCount_;
    return os;
  }

private:
  int num_;
  size_t zeroCount_;
};

std::ifstream validateAndOpenFile(const std::string_view &filename) {
  std::filesystem::path p(filename);
  std::ifstream file;

  if (!std::filesystem::exists(p) || !std::filesystem::is_regular_file(p)) {
    return file;
  }

  file.open(p, std::ios_base::openmode::_S_in);

  return file;
}

std::expected<std::vector<std::string>, std::string> readLines(std::ifstream &file) {
  if (!file.is_open()) {
    return std::unexpected("could not read from file stream");
  }

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

size_t crackSafe(const std::vector<std::string> &safeOperations) {
    SafeDial sd;

    for (const std::string& op : safeOperations) {
        sd += op;
    }

    if constexpr (debug) {
        sd.print(std::cout);
    }

    return sd.zeroCount();
}
