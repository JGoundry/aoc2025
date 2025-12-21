#include "utils/fileUtils.hpp"

#include <expected>
#include <filesystem>

namespace utils
{

std::ifstream validateAndOpenFile(const std::string_view &path) {
  std::filesystem::path p(path);
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

std::expected<std::string, std::string>
read(std::ifstream &file) {
  if (!file.is_open()) {
    return std::unexpected("could not read from file stream");
  }

  std::string data;
  while (!file.eof()) {
    file >> data;
  }

  return data;
}

}
