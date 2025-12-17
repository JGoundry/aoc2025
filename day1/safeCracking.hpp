#include <fstream>
#include <string>
#include <string_view>
#include <vector>

std::ifstream validateAndOpenFile(const std::string_view &filename);
std::vector<std::string> readLines(std::ifstream &file);
size_t crackSafe(const std::vector<std::string>& safeOperations);
