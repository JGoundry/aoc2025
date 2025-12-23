#include "crackSafe.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <expected>
#include <iomanip>
#include <iostream>
#include <string>

#include "utils/stringUtils.hpp"

namespace day1 {
namespace {

const bool debug = std::getenv("AOC_DEBUG");

#define DEBUG_PRINT(msg) \
  if (debug) std::cout << msg << '\n'

std::expected<int, std::exception> safeOpToInt(const std::string& str) {
  try {
    auto num = std::string(str.begin() + 1, str.end());
    return std::stoi(num);

  } catch (const std::exception& e) {
    return std::unexpected(e);
  }
}

class SafeDial {
 public:
  SafeDial& operator+=(const std::string_view& op) {
    // precondition: 0 <= num < 100
    assert(0 <= num_ && num_ < 100);

    // Trim whitespace from operation and check it starts with 'L' or 'R'
    const std::string opTrimmed = utils::trimWhitespace(op);
    if (opTrimmed.empty() || (opTrimmed[0] != 'L' && opTrimmed[0] != 'R')) {
      std::println(std::cerr, "Invalid op: {}", op);
    }

    // Parse number
    const std::expected<int, std::exception> input = safeOpToInt(opTrimmed);
    if (!input) {
      std::println(std::cerr, "Exception when parsing number: {}\n - {}", op,
                   input.error().what());
    }

    DEBUG_PRINT(" - " << opTrimmed);

    if (opTrimmed[0] == 'L') {
      const int div = (num_ - *input) / -100;
      const int mod = (num_ - *input) % -100;

      // If the module is <= 0 it means we have seen zero atleast once, need to
      // count
      if (mod <= 0) {
        // Integer division tells us how many times we went over -100, e.g.
        // (-560 / -100 = 5) Also need to count the additional time, only if the
        // dial didn't start at 0, this would recount it
        zeroCount_ += div + (num_ != 0);
      }

      if (mod >= 0) {  // positive remainder, never crossed 0
        num_ = mod;
      } else {  // negative remainder, need to wrap back round and takeaway the
                // negative value from 100
        num_ = 100 + mod;
      }
    } else {  // 'R'
      const int div = (num_ + *input) / 100;
      const int mod = (num_ + *input) % 100;

      // count how many times we see 0
      zeroCount_ += div;

      num_ = 0 + mod;
    }

    DEBUG_PRINT("    " << std::setw(2) << num_
                       << ", zeroCount = " << zeroCount_);

    // postcondition: 0 <= num < 100
    assert(0 <= num_ && num_ < 100);

    return *this;
  }

  int dialNumber() const { return num_; }

  size_t zeroCount() const { return zeroCount_; }

  void print(std::ostream& os) const { os << *this << '\n'; }

  friend std::ostream& operator<<(std::ostream& os, const SafeDial& sd) {
    os << "Safe num:   " << sd.num_ << '\n' << "Zero count: " << sd.zeroCount_;
    return os;
  }

 private:
  int num_{50};
  size_t zeroCount_{};
};

}  // namespace

std::uint64_t crackSafe(const std::vector<std::string>& safeOperations) {
  SafeDial sd;

  DEBUG_PRINT(sd);

  for (const std::string& op : safeOperations) {
    sd += op;
  }

  DEBUG_PRINT(sd);

  return sd.zeroCount();
}

}  // namespace day1
