#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <string>
#include <c++/limits>

using namespace std;

namespace MyMath {
    class Complex {
    private:
        double re, im, arg, phase;
        void setRe(double re) { Complex::re = re; }
        void setIm(double im) { Complex::im = im; }
        void setArg(double arg) { Complex::arg = arg; }
        void setPhase(double phase) { Complex::phase = phase; }
        void convertPolToRad();
        void converRadToPol();

    public:
        Complex() : Complex(0, 0) {}
        Complex(double r) : Complex(r, 0) {}
        Complex(double x, double y) : re(x), im(y) { convertPolToRad(); }

        double getRe() const { return re; }
        double getIm() const { return im; }
        double getArg() const { return arg; }
        double getPhase() const { return phase; }

        friend double toDouble(Complex num) {
            if(abs(num.getIm()) < numeric_limits<double>::epsilon()) return num.getRe();
            return numeric_limits<double>::quiet_NaN();
        }
        // Returns with 6 nums
        string toString();
        static Complex parse(string const& input);
        static bool tryParse(string const& input, Complex& out_res);

        static Complex pow(Complex arg, double pow);
        static Complex sqrt(Complex arg);

        // TODO: Fix operator signatures
        Complex& operator+=(Complex const& right);
        friend Complex operator+(Complex left, Complex const &right) {
            left += right;
            return left;
        };

        Complex& operator-=(Complex const &right);
        friend Complex operator-(Complex left, Complex const &right) {
            left -= right;
            return left;
        };

        Complex operator-();

        Complex& operator*=(Complex const &right);
        friend Complex operator*(Complex left, Complex const &right) {
            left *= right;
            return left;
        };

        Complex& operator*=(double const &right);
        friend Complex operator*(Complex left, double const &right) {
            left *= right;
            return left;
        };

        Complex& operator/=(Complex const &right);
        friend Complex operator/(Complex left, Complex const &right) {
            left /= right;
            return left;
        };

        Complex& operator/=(double const &right);
        friend Complex operator/(Complex left, double const &right) {
            left /= right;
            return left;
        };
    };
}

#endif //COMPLEX_HPP
