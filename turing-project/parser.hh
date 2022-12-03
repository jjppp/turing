#pragma once

#include "machine.hh"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>

/* Parser for .tm files
 */
namespace parser {

class parser_exception : public std::exception {
  public:
    parser_exception(const std::string &msg) :
        _msg(msg) {
    }

    const char *what() {
        return _msg.c_str();
    }

  private:
    const std::string _msg;
};

void parse_skip(std::string::const_iterator &it);

// parse exactly one character, ignoring leading skips
bool parse_char(std::string::const_iterator &it, char ch);

// parse identifier, ignoring leading skips
std::string parse_id(std::string::const_iterator &it);

// parse a comma seperated list of identifiers
std::vector<std::string> parse_id_list(std::string::const_iterator &it);

vector<char> parse_syms(std::string::const_iterator &it);

State parse_state(std::string::const_iterator &it);

vector<Tape::Direction> parse_dirs(std::string::const_iterator &it);

std::vector<Transition> parse_tran(std::string::const_iterator &it);

Machine parse(const std::string &program, const std::string &input);

Machine parse_file(const std::string &filename, const std::string &input);
} // namespace parser
