#include "solveHomework.hpp"

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>

namespace day6 {
namespace {

const bool debug = std::getenv("AOC_DEBUG");
#define DEBUG_PRINT(msg) \
  if (debug) std::cout << msg << '\n';

enum class Operator : char {
  Add = '+',
  Multiply = '*',
};

template <typename T>
concept OpsT = std::default_initializable<T> && std::constructible_from<T, T> &&
               requires(T a, T b) {
                 { a + b } -> std::convertible_to<T>;
                 { a * b } -> std::convertible_to<T>;
               };

template <OpsT T>
struct Operation {
  std::vector<T> operands;
  Operator op;

  T operator()() const {
    switch (op) {
      case Operator::Add:
        return reduce(std::plus<>{}, T{});
      case Operator::Multiply:
        return reduce(std::multiplies<>{}, T{1});
      default:
        return {};
    }
  }

 private:
  T reduce(const auto& binaryOp, const auto& init) const {
    return std::reduce(operands.begin(), operands.end(), init, binaryOp);
  }
};

}  // namespace

std::uint64_t solveHomework(const std::vector<std::string>& homework) {
  if (homework.size() <= 1) return {};

  auto operations =
      homework.back() | std::views::split(' ') |
      std::views::filter([](const auto& op) { return !op.empty(); }) |
      std::views::transform([](const auto& op) {
        return Operation<std::uint64_t>{.op = static_cast<Operator>(op[0])};
      }) |
      std::ranges::to<std::vector>();

  if (operations.empty()) return {};

  auto rows = homework.size() - 1;
  auto cols =
      std::ranges::max_element(homework, {}, &std::string::size)->size();

  std::println("maxElem: {}", cols);

  auto operationIdx{0};
  for (auto col{0}; col < cols; ++col) {
    std::string word;
    word.reserve(rows);
    for (auto row{0}; row < rows; ++row) {
      if (row >= homework.size() || col >= homework[row].size()) continue;
      const char c = homework[row][col];
      if (c < '0' || c > '9') continue;
      word.push_back(c);
    }

    if (word.empty()) {
      ++operationIdx;
      continue;
    }

    if (operationIdx >= operations.size()) {
      std::println(std::cerr, "ERROR: Ill formed homework.");
      return {};
    }

    try {
      operations[operationIdx].operands.emplace_back(std::stoull(word));

    } catch (const std::exception& e) {
      std::println("Caught exception converting '{}' to number: {}", word,
                   e.what());
    }
  }

  if (debug) {
    for (const auto& operation : operations) {
      std::println("'{}': {} = {}", static_cast<char>(operation.op),
                   operation.operands, operation());
    }
  }

  return std::transform_reduce(operations.begin(), operations.end(),
                               std::uint64_t{}, std::plus<>{},
                               [](const auto& op) { return op(); });
}

}  // namespace day6
