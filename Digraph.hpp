#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP
#include "Bag.hpp"

class Digraph {
    private:
        int _v;
        int _e;
        Bag<int>* adjlist;
        int *indegree;
    public:
        Digraph(int numv = 5) {
            adjlist = new Bag<int>[numv];
            indegree = new int[numv];
            _v = numv;
            _e = 0;
        }
        Digraph(const Digraph& o) {
            _v = o._v;
            _e = o._e;
            indegree = new int[o._v];
            adjlist = new Bag<int>[o._v];
            for (int i = 0; i < o._v; i++) {
                indegree[i] = o.indegree[i];
            }
            for (int i = 0; i < o.V(); i++) {
                if (!o.adjlist[i].empty()) {
                    for (int u : o.adjlist[i]) {
                        addEdge(i, u);
                    }
                }
            }
        }
        ~Digraph() {
            if (adjlist != nullptr) 
                delete [] adjlist;
            if (indegree != nullptr)
                delete [] indegree;
        }
        void addEdge(int v, int w) {
            adjlist[v].add(w);
            indegree[w]++;
            _e++;
        }
        Bag<int>& adj(int v) {
            return adjlist[v];
        }
        int V() const {
            return _v;
        }
        int E() const {
            return _e;
        }
        Digraph operator=(const Digraph& o) {
            _v = o._v;
            _e = o._e;
            indegree = new int[o._v];
            adjlist = new Bag<int>[o._v];
            for (int i = 0; i < o._v; i++) {
                indegree[i] = o.indegree[i];
            }
            for (int i = 0; i < o.V(); i++) {
                if (!o.adjlist[i].empty()) {
                    for (int u : o.adjlist[i]) {
                        addEdge(i, u);
                    }
                }
            }
            return *this;
        }
};


#endif