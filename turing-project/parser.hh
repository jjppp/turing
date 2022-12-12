#pragma once

#include "machine.hh"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>

/* Parser for .tm files
 */
namespace parser {

class parser_exception : public std::exception {
  public:
    static parser_exception of(
        const std::string &msg,
        const size_t       lineno,
        const std::string &expect,
        const char         got) {
        std::stringstream strm;
        strm << msg
             << ", expect " << expect
             << ", got " << got
             << " at line: " << lineno;
        return parser_exception(strm.str());
    }

    const char *what() {
        return _msg.c_str();
    }

  private:
    parser_exception(
        const std::string &msg) :
        _msg(msg) {
    }

    const std::string _msg;
};

Machine parse(const std::string &program, const std::string &input);

Machine parse_file(const std::string &filename, const std::string &input);
} // namespace parser
