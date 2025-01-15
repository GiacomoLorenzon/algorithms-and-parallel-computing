//
// Created by loren on 08/11/2021.
//

#ifndef INITIAL_CODE_COMPLEX_H
#define INITIAL_CODE_COMPLEX_H


class Complex {
private:
    double real = 0.0;
    double img = 0.0;
public:
    // constructor
    Complex(double _real, double _img);

    // getter and setter
    double getReal() const;
    void setReal(double real);
    double getImg() const;
    void setImg(double img);

    // getter : polar
    double getPhase() const;
    double getMod() const;

    // setter : polar
    void setThroughPhase(double phase);
    void setThroughMod(double mod);

    // print
    void print() const;
    void print_polar() const;
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);

#endif //INITIAL_CODE_COMPLEX_H
