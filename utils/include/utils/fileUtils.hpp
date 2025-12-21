#pragma once

#include <expected>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

namespace utils {

std::ifstream validateAndOpenFile(const std::string_view& path);
std::expected<std::vector<std::string>, std::string> readLines(
    std::ifstream& file);
std::expected<std::string, std::string> read(std::ifstream& file);

}  // namespace utils
