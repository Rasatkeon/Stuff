#include <c++/cmath>
#include "Complex.hpp"

using namespace std;
using namespace MyMath;

void Complex::convertPolToRad() {
    setArg(std::sqrt(std::pow(getRe(), 2) + std::pow(getIm(), 2)));
    setPhase(atan2(getIm(), getRe()));
}

void Complex::converRadToPol() {
    setRe(cos(getPhase()) * getArg());
    setIm(sin(getPhase()) * getArg());
}

string Complex::toString() {
    return "(" + to_string(getRe()) + ";" + to_string(getIm()) + ")";
}

// TODO: Implement parse and tryparse
Complex Complex::parse(string const &input) {
    return Complex();
}

bool Complex::tryParse(string const &input, Complex &out_res) {
    return false;
}

Complex Complex::pow(Complex arg, double pow) {
    Complex res;
    res.setArg(std::pow(arg.getArg(), pow));
    res.setPhase(arg.getPhase() * pow);
    res.converRadToPol();
    return res;
}

Complex Complex::sqrt(Complex arg) {
    return pow(arg, 0.5);
}

Complex& Complex::operator+=(Complex const& right) {
    setRe(getRe() + right.getRe());
    setIm(getIm() + right.getIm());
    convertPolToRad();
    return *this;
}

Complex& Complex::operator-=(Complex const& right) {
    setRe(getRe() - right.getRe());
    setIm(getIm() - right.getIm());
    convertPolToRad();
    return *this;
}

Complex Complex::operator-() {
    setIm(-getIm());
    setRe(-getRe());
    convertPolToRad();
    return *this;
}

Complex& Complex::operator*=(Complex const& right) {
    setArg(getArg() * right.getArg());
    setPhase(getPhase() + right.getPhase());
    converRadToPol();
    return *this;
}

Complex& Complex::operator*=(double const& right) {
    setArg(getArg() * right);
    converRadToPol();
    return *this;
}

Complex& Complex::operator/=(Complex const& right) {
    setArg(getArg() / right.getArg());
    setPhase(getPhase() - right.getPhase());
    converRadToPol();
    return *this;
}

Complex& Complex::operator/=(double const& right) {
    setArg(getArg() / right);
    converRadToPol();
    return *this;
}

