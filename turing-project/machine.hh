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
    State(const std::string &name) :
        _name(name) {
    }

    auto name() -> std::string {
        return _name;
    }

    bool operator==(const State &rhs) const {
        return _name == rhs._name;
    }

    bool operator!=(const State &rhs) const {
        return !(*this == rhs);
    }

  private:
    std::string _name;
};

class Transition {
  public:
    Transition(
        State                   old_state,
        State                   new_state,
        vector<char>            old_syms,
        vector<char>            new_syms,
        vector<Tape::Direction> dirs,
        size_t                  n) :
        _old_state(old_state),
        _new_state(new_state),
        _old_syms(old_syms),
        _new_syms(new_syms),
        _dirs(dirs),
        _n(n) {
    }

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

    vector<Tape::Direction> dirs() const {
        return _dirs;
    }

    size_t n_tape() const {
        return _n;
    }

    bool match(State cur_state, vector<char> cur_syms) const;

  private:
    using Direction = Tape::Direction;

    State             _old_state, _new_state;
    vector<char>      _old_syms, _new_syms;
    vector<Direction> _dirs;
    size_t            _n;
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

    size_t n_step() const {
        return _n_step;
    }

    std::string output();

    bool step(bool is_verbose);

  private:
    const vector<Transition> _transitions;
    const size_t             _n;
    vector<Tape>             _tapes;
    State                    _state;
    size_t                   _n_step;

    void print_vec(const std::string &spec, const std::vector<std::string> &vec) const;
};