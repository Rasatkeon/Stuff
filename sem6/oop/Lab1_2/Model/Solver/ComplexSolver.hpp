#ifndef COMPLEXSOLVER_HPP
#define COMPLEXSOLVER_HPP

#include <c++/limits>
#include <c++/cmath>
#include <c++/vector>
#include "ASolver.hpp"
#include "Complex.hpp"

using namespace MyMath;
using namespace std;

namespace Solver {
    class ComplexSolver : ASolver<Complex> {
    protected:
        Complex computeSqD(Complex a, Complex b, Complex c) override {
            return Complex::sqrt(Complex::pow(b, 2) - 4*a*c);
        }

        Complex calculateY(Complex x) override {
            return getA()*Complex::pow(x, 2) + getB()*x + getC();
        }
    public:
        ComplexSolver(Complex const& a, Complex const& b, Complex const& c) : ASolver(a, b, c) {}

        vector<Complex> solve() override {
            auto sqD = computeSqD(getA(),getB(), getC());
            if (sqD.getArg() < std::numeric_limits<double>::epsilon()*sqrt(2)) {
                return { -getB() / (getA() * 2) };
            }
            else {
                return {
                        (-getB() + sqD) / (getA() * 2),
                        (-getB() - sqD) / (getA() * 2)
                };
            };
        }
    };
}

#endif //COMPLEXSOLVER_HPP
