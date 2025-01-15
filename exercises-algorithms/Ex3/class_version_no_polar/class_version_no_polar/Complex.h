//
// Created by Federica Filippini on 14/10/2021.
//

#ifndef NEW_COMPLEX_COMPLEX_H
#define NEW_COMPLEX_COMPLEX_H


class Complex {

private:
    double m_real = 0.0;
    double m_img = 0.0;

public:
    Complex(double real, double img);

    double getMReal() const;

    void setMReal(double mReal);

    double getMImg() const;

    void setMImg(double mImg);

    double getModulus() const;
    void setModulus(double mod);

    double getPhase() const;
    void setPhase(double phase);

    void print() const;
    void print_polar() const;
};

Complex operator+ (const Complex&, const Complex&);
Complex operator- (const Complex&, const Complex&);
Complex operator* (const Complex&, const Complex&);
Complex operator/ (const Complex&, const Complex&);



#endif //NEW_COMPLEX_COMPLEX_H
