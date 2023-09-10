#ifndef GREP_HPP
#define GREP_HPP
#include "NFA.hpp"

bool grep(string regexp, string text) {
    string full = "(.*" + regexp + ".*)";
    NFA nfa(full);
    return nfa.recognizes(text);
}

#endif