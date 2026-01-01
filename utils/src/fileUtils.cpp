#include "utils/fileUtils.hpp"

#include <expected>
#include <filesystem>
#include <ios>
#include <system_error>

namespace utils {

std::ostream& operator<<(std::ostream& os, const FileError& err) {
  os << "FileError[" << err.path << "]: ";
  switch (err.code) {
    case FileErrorCode::FileNotFound:
      os << "File not found.";
      break;
    case FileErrorCode::NotAFile:
      os << "Not a file.";
      break;
    case FileErrorCode::PermissionDenied:
      os << "Permission denied.";
      break;
    case FileErrorCode::FileNotOpen:
      os << "File not open.";
      break;
    case FileErrorCode::Unknown:
      os << "Unknown.";
      break;
  }
  if (!err.message.empty()) {
    os << "(" << err.message << ")";
  }
  return os;
}

std::expected<std::ifstream, FileError> openFile(
    const std::string_view& path, const std::ios_base::openmode mode) {
  std::filesystem::path p(path);

  std::error_code ec;

  // 1. Check filepath exists
  if (!std::filesystem::exists(p, ec)) {
    return std::unexpected(
        FileError{p, FileErrorCode::FileNotFound, (ec ? ec.message() : std::string{}) });
  }

  // 2. File type check
  if (!std::filesystem::is_regular_file(p)) {
    return std::unexpected(FileError{p, FileErrorCode::NotAFile, (ec ? ec.message() : std::string{})});
  }

  // 3. Open file
  std::ifstream file(p, mode);
  if (!file) {
    return std::unexpected(
        FileError{p, FileErrorCode::PermissionDenied, "Failed to open file."});
  }

  return file;
}

std::expected<std::vector<std::string>, FileError> readLines(
    std::ifstream& file) {
  if (!file) {
    return std::unexpected(FileError{
        std::filesystem::path{}, FileErrorCode::Unknown, "Unknow failure."});
  }

  if (!file.is_open()) {
    return std::unexpected(FileError{
        std::filesystem::path{}, FileErrorCode::FileNotOpen, "File not open."});
  }

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

std::expected<std::string, FileError> read(std::ifstream& file) {
  if (!file) {
    return std::unexpected(FileError{
        std::filesystem::path{}, FileErrorCode::Unknown, "Unknow failure."});
  }

  if (!file.is_open()) {
    return std::unexpected(FileError{
        std::filesystem::path{}, FileErrorCode::FileNotOpen, "File not open."});
  }

  std::string data;
  while (!file.eof()) {
    file >> data;
  }

  return data;
}

}  // namespace utils
