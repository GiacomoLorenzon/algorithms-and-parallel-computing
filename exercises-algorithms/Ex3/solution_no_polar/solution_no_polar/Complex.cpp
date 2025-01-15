//
// Created by Federica Filippini on 12/10/2021.
//

#include "Complex.h"

#include <iostream>
#include <cmath>
#include <limits>

Complex::Complex(double real, double img): m_real(real), m_img(img) {}

double Complex::get_real() const
{
    return m_real;
}

double Complex::get_img() const
{
    return m_img;
}

double Complex::get_modulus() const
{
    return sqrt(m_img*m_img + m_real*m_real);
}

double Complex::get_phase() const
{
    double phase = std::numeric_limits<double>::quiet_NaN();
    double sign = m_img >= 0 ? 1.0 : -1.0;

    if (m_real > 0.0)
        phase = atan(m_img / m_real);
    else if (m_real < 0.0)
        phase = atan(m_img / m_real) + sign * M_PI;
    else {
        if (m_img > 0.0 || m_img < 0.0)
            phase = sign * M_PI / 2.0;
    }

    return phase;
}

void Complex::set_real(double real)
{
    m_real = real;
}

void Complex::set_img(double img)
{
    m_img = img;
}

void Complex::set_modulus(double mod)
{
    double ph = get_phase();
    m_real = mod * cos(ph);
    m_img = mod * sin(ph);
}

void Complex::set_phase(double phase)
{
    double mod = get_modulus();
    m_real = mod * cos(phase);
    m_img = mod * sin(phase);
}

void Complex::print() const
{
    std::cout << m_real << " + " << m_img << "i" << std::endl;
}

void Complex::print_polar() const
{
    std::cout << get_modulus() << "[cos(" << get_phase() << ") + i sin("
                << get_phase() << ")]" << std::endl;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
    double real = lhs.get_real() + rhs.get_real();
    double img = lhs.get_img() + rhs.get_img();
    return Complex(real, img);
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
    double real = lhs.get_real() - rhs.get_real();
    double img = lhs.get_img() - rhs.get_img();
    return Complex(real, img);
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
    double real = lhs.get_real() * rhs.get_real() - lhs.get_img() * rhs.get_img();
    double img = lhs.get_img() * rhs.get_real() + lhs.get_real() * rhs.get_img();
    return Complex(real, img);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    double den = rhs.get_real() * rhs.get_real() + rhs.get_img() * rhs.get_img();
    double r_num = lhs.get_real() * rhs.get_real() + lhs.get_img() * rhs.get_img();
    double i_num = lhs.get_img() * rhs.get_real() - lhs.get_real() * rhs.get_img();
    return Complex(r_num/den, i_num/den);
}
