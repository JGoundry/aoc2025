#pragma once

#include <expected>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace utils {

enum class FileErrorCode : std::uint8_t {
  FileNotFound = 0,
  NotAFile,
  PermissionDenied,
  FileNotOpen,
  Unknown,
};

struct FileError {
  std::filesystem::path path;
  FileErrorCode code;
  std::string message;

  friend std::ostream& operator<<(std::ostream& os, const FileError& err);
};

std::expected<std::ifstream, FileError> openFile(const std::string_view& path,
                                                 std::ios_base::openmode mode);

std::expected<std::vector<std::string>, FileError> readLines(
    std::ifstream& file);

std::expected<std::string, FileError> read(std::ifstream& file);

}  // namespace utils
