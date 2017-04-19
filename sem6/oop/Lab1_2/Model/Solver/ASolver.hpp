#ifndef ASOLVER_H
#define ASOLVER_H

#include <c++/vector>

namespace Solver {
    template <class T>
    class ASolver {

    private:
        T a;
        T b;
        T c;

    public:
        T getA() const { return a; }
        void setA(T a) { ASolver::a = a; }

        T getB() const { return b; }
        void setB(T b) { ASolver::b = b; }

        T getC() const { return c; }
        void setC(T c) { ASolver::c = c; }

        void setParams(T a, T b, T c) { setA(a), setB(b), setC(c); }
        ASolver(T a, T b, T c) : a(a), b(b), c(c) {}

        virtual vector<T> solve() = 0;
        virtual T calculateY(T x) = 0;
    protected:
        virtual T computeSqD(T a, T b, T c) = 0;
    };
}

#endif // ASOLVER_H
