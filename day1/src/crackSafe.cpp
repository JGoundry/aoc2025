#include "crackSafe.hpp"

#include "utils/stringUtils.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <iomanip>

bool debug = std::getenv("AOC_DEBUG");

#define DEBUG_PRINT(msg)                                                       \
  if (debug)                                                         \
    std::cout << msg << '\n';

int safeOpToInt(const std::string &str) {
  try {
    auto num = std::string(str.begin() + 1, str.end());
    return std::stoi(num);

  } catch (const std::exception &e) {
    std::cerr << "Caught exception: " << e.what() << '\n';
    return 0;
  }
}

class SafeDial {
public:
  SafeDial() : num_(50), zeroCount_(0) {}

  SafeDial &operator+=(const std::string_view &op) {
    // precondition: 0 <= num < 100
    assert(0 <= num_ && num_ < 100);

    const std::string opTrimmed = trimWhitespace(op);

    DEBUG_PRINT(" - " << opTrimmed);

    switch (opTrimmed[0]) {
    case 'L': {
      const int input = safeOpToInt(opTrimmed);
      const int div = (num_ - input) / -100;
      const int mod = (num_ - input) % -100;

      // count how many times we see 0
      if (mod <= 0) {
        // only add another 0 if we werent already on 0 so we don't count it twice
        zeroCount_ += div + (num_ != 0); 
      }

      if (mod >= 0) { // positive remainder
        num_ = mod;
      } else { // negative remainder
        num_ = 100 + mod;
      }

      break;
    }
    case 'R': {
      const int input = safeOpToInt(opTrimmed);
      const int div = (num_ + input) / 100;
      const int mod = (num_ + input) % 100;

      // count how many times we see 0
      zeroCount_ += div;

      num_ = 0 + mod;

      break;
    }
    default: {
      std::cerr << "Invalid op: " << op << '\n';
      break;
    }
    }

    DEBUG_PRINT("    " << std::setw(2) << num_ << ", zeroCount = " << zeroCount_ );

    // postcondition: 0 <= num < 100
    assert(0 <= num_ && num_ < 100);

    return *this;
  }

  int dialNumber() const { return num_; }

  size_t zeroCount() const { return zeroCount_; }

  void print(std::ostream &os) const { os << *this << '\n'; }

  friend std::ostream &operator<<(std::ostream &os, const SafeDial &sd) {
    os << "Safe num:   " << sd.num_ << '\n' << "Zero count: " << sd.zeroCount_;
    return os;
  }

private:
  int num_;
  size_t zeroCount_;
};

size_t crackSafe(const std::vector<std::string> &safeOperations) {
  SafeDial sd;

  DEBUG_PRINT(sd);

  for (const std::string &op : safeOperations) {
    sd += op;
  }

  DEBUG_PRINT(sd);

  return sd.zeroCount();
}
