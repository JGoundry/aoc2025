#include "fileUtils.hpp"

#include <expected>
#include <filesystem>

std::ifstream validateAndOpenFile(const std::string_view &filename) {
  std::filesystem::path p(filename);
  std::ifstream file;

  if (!std::filesystem::exists(p) || !std::filesystem::is_regular_file(p)) {
    return file;
  }

  file.open(p, std::ios_base::openmode::_S_in);

  return file;
}

std::expected<std::vector<std::string>, std::string>
readLines(std::ifstream &file) {
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

