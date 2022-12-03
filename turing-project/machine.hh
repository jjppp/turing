#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <list>

using std::vector;

class Tape {
  public:
    enum Direction {
        L,
        R,
        N
    };

    Tape(char blank);

    Tape(char blank, std::string input);

    char cur_sym() const {
        return _cur->_content;
    }

    int cur_index() const {
        return _cur->_index;
    }

    void write(char new_sym) {
        _cur->_content = new_sym;
    }

    void move(Direction dir);

    // return contents on tape, with leading and trailing blanks stripped
    std::string to_string();

    std::vector<std::pair<char, int>> to_vec();

  private:
    struct Node {
        std::shared_ptr<Node> _next, _prev;
        char                  _content;
        int                   _index;
    };

    void gc();

    std::shared_ptr<Node> _cur, _lm, _rm;
    const char            _blank;
};

class State {
  public:
    auto name() -> std::string {
        return _name;
    }

    bool operator==(const State &rhs) const {
        return _id == rhs._id && _name == rhs._name;
    }

  private:
    std::string _name;
    size_t      _id;
};

class Transition {
  public:
    State old_state() const {
        return _old_state;
    }

    State new_state() const {
        return _new_state;
    }

    vector<char> old_syms() const {
        return _old_syms;
    }

    vector<char> new_syms() const {
        return _new_syms;
    }

    Tape::Direction dir() const {
        return _dir;
    }

    size_t n_tape() const {
        return _n;
    }

    bool match(State cur_state, vector<char> cur_syms) const;

  private:
    using Direction = Tape::Direction;

    State        _old_state, _new_state;
    vector<char> _old_syms, _new_syms;
    Direction    _dir;
    size_t       _n;
};

class Machine {
  public:
    Machine(
        size_t                    n,
        const std::string        &input,
        const vector<Transition> &transitions,
        const State              &initial_state);

    size_t n_tape() const {
        return _n;
    }

    void step();

  private:
    const vector<Transition> _transitions;
    const size_t             _n;
    vector<Tape>             _tapes;
    State                    _state;
};