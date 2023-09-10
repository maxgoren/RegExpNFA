#include <iostream>
#include "Bag.hpp"
#include "GREP.hpp"
using namespace std;

int main() {
    Bag<string> strs;
    strs.add("AC").add("AD").add("AAA").add("ABD")
        .add("ADD").add("BCD").add("ABCCBD").add("BABAAA")
        .add("BABBAAA");
    string regexp = "(A*B|AC)D";
    for (string s : strs) {
        if (grep(regexp, s))
            cout<<s<<endl;
    }
    return 0;
}