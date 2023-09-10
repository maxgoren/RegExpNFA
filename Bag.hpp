#ifndef BAG_HPP
#define BAG_HPP
#include "Iterator.hpp"

template <class T>
class Bag {
    private:
        T* a;
        int n;
        int maxn;
        void resize(int newsize) {
            T* tmp = new T[newsize];
            for (int i = 0; i < n; i++)
                tmp[i] = a[i];
            delete [] a;
            a = tmp;
            maxn = newsize;
        }
    public:
        Bag(int initsize = 10) {
            a = new T[initsize];
            maxn = initsize;
            n = 0;
        }
        Bag(const Bag& o) {
            n = o.n;
            maxn = o.maxn;
            a = new T[o.maxn];
            for (int i = 0; i < o.n; i++)
                a[i] = o.a[i];
        }
        ~Bag() {
            if (a != nullptr) delete [] a;
        }
        Bag& add(T info) {
            if (n+1 == maxn) resize(2*maxn);
            a[n++] = info;
            return *this;
        }
        int size() const {
            return n;
        }
        bool empty() const {
            return n == 0;
        }
        Iterator<T> begin() {
            return Iterator<T>(a);
        }
        Iterator<T> end() {
            return Iterator<T>(a+n);
        }
        Bag operator=(const Bag& o) {
            n = o.n;
            maxn = o.maxn;
            a = new T[o.maxn];
            for (int i = 0; i < o.n; i++)
                a[i] = o.a[i];
            return *this;
        }
};

#endif