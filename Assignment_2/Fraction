#include <iostream>
using namespace std;

class Fraction {
private:
    int numerator, denominator;

public:
    Fraction(int n = 0, int d = 1) : numerator(n), denominator(d) {}

    Fraction add(const Fraction &f) {
        return Fraction(numerator * f.denominator +
                        f.numerator * denominator,
                        denominator * f.denominator);
    }

    Fraction subtract(const Fraction &f) {
        return Fraction(numerator * f.denominator -
                        f.numerator * denominator,
                        denominator * f.denominator);
    }

    void display() const {
        cout << numerator << "/" << denominator << endl;
    }
};

int main() {
    Fraction f1(1, 2), f2(3, 4);

    Fraction sum = f1.add(f2);
    Fraction diff = f1.subtract(f2);

    cout << "First Fraction: ";
    f1.display();

    cout << "Second Fraction: ";
    f2.display();

    cout << "Addition: ";
    sum.display();

    cout << "Subtraction: ";
    diff.display();

    return 0;
}
