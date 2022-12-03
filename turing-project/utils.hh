#pragma once

#include <algorithm>
#include <string>

namespace utils {

void lstrip(std::string &str, char ch);

void rstrip(std::string &str, char ch);

void strip(std::string &str, char ch);

} // namespace utils