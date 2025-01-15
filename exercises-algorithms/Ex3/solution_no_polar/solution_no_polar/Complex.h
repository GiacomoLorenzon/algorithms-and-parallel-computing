//
// Created by Federica Filippini on 12/10/2021.
//

#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H

class Complex {

private:
    double m_real;
    double m_img;

public:
    // constructor
    Complex(double, double);

    // getters
    double get_real() const;
    double get_img() const;
    double get_modulus() const;
    double get_phase() const;

    // setters
    void set_real(double);
    void set_img(double);
    void set_modulus(double);
    void set_phase(double);

    // print
    void print() const;
    void print_polar() const;
};

// operators
Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);

#endif //COMPLEX_COMPLEX_H
