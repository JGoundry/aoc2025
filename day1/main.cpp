#include <fstream>
#include <iostream>

#include "safeCracking.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return -1;
  }

  // Validate filepath and open file
  const std::string_view filename = argv[1];
  std::ifstream file = validateAndOpenFile(filename);
  
  // Read lines from file
  const std::expected<std::vector<std::string>, std::string> safeOps = readLines(file);
  if (!safeOps) {
      std::cerr << safeOps.error() << '\n';
      return -1;
  }

  const size_t code = crackSafe(safeOps.value());

  return code;
}
