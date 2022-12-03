#include "utils.hh"

namespace utils {

void lstrip(std::string &str, char ch) {
    str.erase(str.begin(),
              std::find_if(str.begin(), str.end(), [ch](char x) {
                  return ch != x;
              }));
}

void rstrip(std::string &str, char ch) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [ch](char x) {
                  return ch != x;
              }).base(),
              str.end());
}

void strip(std::string &str, char ch) {
    rstrip(str, ch);
    lstrip(str, ch);
}

} // namespace utils