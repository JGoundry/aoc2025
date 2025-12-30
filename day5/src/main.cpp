#include <iostream>
#include <print>

#include "totalFreshIngredients.hpp"
#include "utils/fileUtils.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::println(std::cerr, "Usage: {} <input_file>", argv[0]);
    return -1;
  }

  // Validate filepath and open file
  const std::string_view filename = argv[1];
  auto file = utils::openFile(filename, std::ios_base::in);
  if (!file) {
    std::cerr << file.error() << '\n';
    return -1;
  }

  // Read lines from file
  const auto& database = utils::readLines(*file);
  if (!database) {
    std::cerr << database.error() << '\n';
    return -1;
  }

  const auto totalFreshIngredients = day5::totalFreshIngredients(*database);

  std::println("Total fresh ingredients: {}", totalFreshIngredients);

  return 0;
}
