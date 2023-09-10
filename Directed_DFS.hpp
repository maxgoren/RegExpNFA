#ifndef DIRECTED_DFS_HPP
#define DIRECTED_DFS_HPP
#include "Digraph.hpp"

class DirectedDFS {
    private:
        bool* seen;
        int numv;
        void search(Digraph& G, int v) {
            numv = G.V();
            seen[v] = true;
            for (int u : G.adj(v))
                if (!seen[u])
                    search(G, u);
        }
        void initseen(size_t size) {
            seen = new bool[size];
            for (int i = 0; i < size; i++)
                seen[i] = false;
        }
    public:
        DirectedDFS(Digraph& G, int v) {
            initseen(G.V());
            search(G, v);
        }
        DirectedDFS(Digraph& G, Bag<int>& src) {
            initseen(G.V());
            for (int v : src)
                if (!seen[v])
                    search(G, v);
        }
        DirectedDFS(const DirectedDFS& o) {
            if (o.numv > 0) {
                numv = o.numv;
                seen = new bool[numv];
                for (int i = 0; i < numv; i++)
                    seen[i] = o.seen[i];
            }
        }
        ~DirectedDFS() {
            if (seen != nullptr) 
                delete [] seen;
        }
        bool marked(int v) {
            return seen[v];
        }
        DirectedDFS operator=(const DirectedDFS& o) {
            if (o.numv > 0) {
                numv = o.numv;
                seen = new bool[numv];
                for (int i = 0; i < numv; i++)
                    seen[i] = o.seen[i];
            }
            return *this;
        }
};


#endif