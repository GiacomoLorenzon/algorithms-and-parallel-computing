//
// Created by loren on 08/11/2021.
//

#include "Complex.h"

#include <cmath>
#include <limits>
#include <iostream>

using std::cout;
using std::endl;

// constructor
Complex::Complex(double _real, double _img) : real(_real), img(_img) {}

// setter and getter
double Complex::getReal() const {
    return real;
}
void Complex::setReal(double real) {
    Complex::real = real;
}
double Complex::getImg() const {
    return img;
}
void Complex::setImg(double img) {
    Complex::img = img;
}

// getter : polar
double Complex::getPhase() const
{
    double phase = std::numeric_limits<double>::quiet_NaN();
    double sign = img >= 0 ? 1.0 : -1.0;

    if (real > 0)
        phase = atan(img / real);
    else if (real < 0)
        phase = atan(img / real) + sign * M_PI;
    else
        if (img != 0)
            phase = sign * M_PI / 2;

    return phase;
}
double Complex::getMod() const {
    return sqrt(real*real + img*img);
}

// setter : polar
void Complex::setThroughPhase(double phase)
{
    double mod = getMod();
    real = mod * cos(phase);
    img = mod * sin(phase);
}
void Complex::setThroughMod(double mod)
{
    double phase = getPhase();
    real = mod * cos(phase);
    img = mod * sin(phase);
}

// print
void Complex::print() const
{
    cout << real << " + " << img << "i" << endl;
}
void Complex::print_polar() const
{
    cout << getMod() << " [cos(" << getPhase() << ") + i sin(" << getPhase() << ")]" << endl;
}

Complex operator+(const Complex& lhs, const Complex& rhs){
    double real = lhs.getReal() + rhs.getReal();
    double img = lhs.getImg() + rhs.getImg();
    return Complex(real, img);
}
Complex operator-(const Complex& lhs, const Complex& rhs){
    double real = lhs.getReal() - rhs.getReal();
    double img = lhs.getImg() - rhs.getImg();
    return Complex(real, img);
}
Complex operator*(const Complex& lhs, const Complex& rhs){
    double real = lhs.getReal()*rhs.getReal() - lhs.getImg()*rhs.getImg();
    double img = lhs.getImg()*rhs.getReal() - lhs.getReal()*rhs.getImg();
    return Complex(real, img);
}
Complex operator/(const Complex& lhs, const Complex& rhs){
    double den = rhs.getReal() * rhs.getReal() + rhs.getImg() * rhs.getImg();
    double real = lhs.getReal()*rhs.getReal() + lhs.getImg()*rhs.getImg();
    double img = lhs.getImg()*rhs.getReal() - lhs.getReal()*rhs.getImg();
    return Complex(real / den, img / den);
}