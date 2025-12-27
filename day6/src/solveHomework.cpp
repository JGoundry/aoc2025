#include "solveHomework.hpp"

#include <concepts>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>

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
concept OpsT = std::default_initializable<T> &&
               std::constructible_from<T, int> && requires(T a, T b) {
                 { a + b } -> std::convertible_to<T>;
                 { a * b } -> std::convertible_to<T>;
               };

template <OpsT T>
using Operands = std::vector<T>;

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
        return 0;
    }
  }

 private:
  T reduce(const auto& binaryOp, const auto& init) const {
    return std::reduce(operands.begin(), operands.end(), init, binaryOp);
  }
};

}  // namespace

std::uint64_t solveHomework(const std::vector<std::string>& homework) {
  if (homework.empty()) return {};

  auto operations =
      homework.back() | std::views::split(' ') |
      std::views::filter([](const auto& op) { return !op.empty(); }) |
      std::views::transform([](const auto& op) {
        return Operation<std::uint64_t>{.op = static_cast<Operator>(op[0])};
      }) |
      std::ranges::to<std::vector>();

  if (operations.empty()) return {};

  auto allOperands =
      homework | std::views::take(homework.size() - 1) |
      std::views::transform([](const std::string& row) {
        return row | std::views::split(' ') |
               std::views::filter([](auto&& charRange) {
                 return !std::ranges::empty(charRange);
               }) |
               std::views::transform([](auto&& charRange) {
                 return std::stoull(std::string(std::string_view(charRange)));
               });
      }) |
      std::views::join;

  for (auto&& [idx, operand] : allOperands | std::views::enumerate) {
    operations[idx % operations.size()].operands.emplace_back(operand);
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
