#ifndef DOUBLESOLVER_H
#define DOUBLESOLVER_H

#include <c++/cmath>
#include <c++/vector>
#include <c++/limits>
#include "ASolver.hpp"

using namespace std;

namespace Solver {
    class DoubleSolver : public ASolver<double> {
    protected:
        double computeSqD(double a, double b, double c) override {
            return sqrt(pow(b, 2) - 4*a*c);
        }
    public:
        DoubleSolver(double a, double b, double c) : ASolver(a, b, c) {}
        vector<double> solve() override {
            auto sqD = computeSqD(getA(), getB(), getC());
            if(isnan(sqD)) {
                return { numeric_limits<double>::quiet_NaN() };
            }
            else if (abs(sqD) < numeric_limits<double>::epsilon()) {
                return { -getB() / (2 * getA()) };
            }
            else {
                return { (-getB() + sqD)/(2*getA()),
                         (-getB() - sqD)/(2*getA()) };
            }
        }
        double calculateY(double x) override {
            return getA()*pow(x, 2) + getB()*x + getC();
        }
    };
}

#endif //DOUBLESOLVER_H
