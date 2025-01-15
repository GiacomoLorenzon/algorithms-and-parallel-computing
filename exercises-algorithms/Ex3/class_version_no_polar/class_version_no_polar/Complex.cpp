//
// Created by Federica Filippini on 14/10/2021.
//

#include "Complex.h"

#include <cmath>
#include <limits>
#include <iostream>

using std::cout;
using std::endl;

Complex::Complex(double real, double img) : m_real(real), m_img(img) {}

double Complex::getMReal() const {
    return m_real;
}

void Complex::setMReal(double mReal) {
    m_real = mReal;
}

double Complex::getMImg() const {
    return m_img;
}

void Complex::setMImg(double mImg) {
    m_img = mImg;
}

double Complex::getModulus() const
{
    return sqrt(m_real * m_real + m_img * m_img);
}

void Complex::setModulus(double mod)
{
    double phase = getPhase();
    m_real = mod * cos(phase);
    m_img = mod * sin(phase);
}

double Complex::getPhase() const
{
    double phase = std::numeric_limits<double>::quiet_NaN();
    double sign = m_img >= 0 ? 1.0 : -1.0;
/*
    double sign;
    if (m_img >= 0)
        sign = 1.0;
    else
        sign = -1.0;
*/

    if (m_real > 0)
    {
        phase = atan(m_img / m_real);
    }
    else if (m_real < 0)
    {
        phase = atan(m_img / m_real) + sign * M_PI;
    }
    else {
        if (m_img != 0)
            phase = sign * M_PI / 2.0;    // M_PI_2
    }

    /*
    if (m_real == 0)
    {
        // false
    }
     */

    return phase;
}

void Complex::setPhase(double phase)
{
    double mod = getModulus();
    m_real = mod * cos(phase);
    m_img = mod * sin(phase);
}

void Complex::print() const
{
    cout << m_real << " + " << m_img << "i" << endl;
}

void Complex::print_polar() const
{
    cout << getModulus() << "[cos(" << getPhase()
        << ") + i sin(" << getPhase() << ")]" << endl;
}

Complex operator+ (const Complex& lhs, const Complex& rhs)
{
    double real = lhs.getMReal() + rhs.getMReal();
    double img = lhs.getMImg() + rhs.getMImg();
    Complex res(real, img);
    return res;                 //Complex(real, img);
}

Complex operator- (const Complex& lhs, const Complex& rhs)
{
    double real = lhs.getMReal() - rhs.getMReal();
    double img = lhs.getMImg() - rhs.getMImg();
    Complex res(real, img);
    return res;                 //Complex(real, img);
}

Complex operator* (const Complex& lhs, const Complex& rhs)
{
    double real = lhs.getMReal() * rhs.getMReal() -
                    lhs.getMImg() * rhs.getMImg();
    double img = lhs.getMImg() * rhs.getMReal() +
                 lhs.getMReal() * rhs.getMImg();
    return Complex(real, img);
}

Complex operator/ (const Complex& lhs, const Complex& rhs)
{
    double den = rhs.getMReal() * rhs.getMReal() +
                    rhs.getMImg() * rhs.getMImg();
    double r_num = lhs.getMReal() * rhs.getMReal() +
                   lhs.getMImg() * rhs.getMImg();
    double i_num = lhs.getMImg() * rhs.getMReal() -
                   lhs.getMReal() * rhs.getMImg();
    return Complex(r_num / den, i_num / den);
}
