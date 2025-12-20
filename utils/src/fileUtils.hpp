#include <fstream>
#include <expected>
#include <string_view>
#include <vector>
#include <string>

std::ifstream validateAndOpenFile(const std::string_view &filename);
std::expected<std::vector<std::string>, std::string> readLines(std::ifstream &file);
