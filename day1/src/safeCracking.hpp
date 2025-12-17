#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <expected>

std::ifstream validateAndOpenFile(const std::string_view &filename);
std::expected<std::vector<std::string>, std::string> readLines(std::ifstream &file);
size_t crackSafe(const std::vector<std::string>& safeOperations);
