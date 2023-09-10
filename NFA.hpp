#ifndef NFA_HPP
#define NFA_HPP
#include <iostream>
#include "Digraph.hpp"
#include "Bag.hpp"
#include "Stack.hpp"
#include "Directed_DFS.hpp"
using std::cout;
using std::endl;
using std::string;

class NFA {
    private:
        Digraph G;
        string regexp;
        int m;
    public:
        NFA(string regex) {
            regexp = regex;
            m = regexp.length();
            G = Digraph(m+1);
            Stack<int> ops;
            for  (int i = 0; i < m; i++) {
                int lp = i;
                if (regexp.at(i) == '(' || regexp.at(i) == '|')
                    ops.push(i);
                else if (regexp.at(i) == ')')
                {
                    int ro = ops.pop();
                    if (regexp.at(ro) == '|') {
                        lp = ops.pop();
                        G.addEdge(lp, ro+1);
                        G.addEdge(ro, i);
                    } else lp = ro;
                }
                if (i < m-1 && regexp.at(i+1) == '*') {
                    G.addEdge(lp, i+1);
                    G.addEdge(i+1, lp);
                }
                if (regexp.at(i) == '(' || regexp.at(i) == '*' || regexp.at(i) == ')')
                    G.addEdge(i, i+1);
            }
            if (!ops.empty()) {
                cout<<"Something went wrong building NFA: matching may not(most likely wont..) work."<<endl;
            }
        }
        bool recognizes(string txt) {
            auto dfs = DirectedDFS(G, 0);
            auto pc = Bag<int>();
            for (int v = 0; v < G.V(); v++)
                if (dfs.marked(v)) pc.add(v);
            
            for (int i = 0; i < txt.length(); i++) {
                auto states = Bag<int>();
                for (int v : pc)
                    if (v != m) 
                        if (regexp.at(v) == txt.at(i) || regexp.at(v) == '.')
                            states.add(v+1);
                pc = Bag<int>();
                dfs = DirectedDFS(G, states);
                for (int v = 0; v < G.V(); v++)
                    if (dfs.marked(v))
                        pc.add(v);
                if (pc.empty())
                    return false;
            }
            for (int v : pc) if (v == m) return true;
            return false;
        }
};

#endif