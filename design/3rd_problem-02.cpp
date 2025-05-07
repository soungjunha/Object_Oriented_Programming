#include <iostream>

using namespace std;

class Complex {
private:
	double real;
	double imag;

	// Write your code here -> Implement member variables and helper functions

public:
	Complex(double real, double imag) :real(real), imag(imag) {}
	Complex operator+(const Complex& other);
	Complex operator-(const Complex& other);
	Complex operator*(const Complex& other);
	Complex operator/(const Complex& other);
	void print();
	// Write your code here -> Implement constructor, overloaded operators: +, -, *, /, print function
};

Complex Complex::operator+(const Complex& other) {
	return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) {
	return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) {
	double r = this->real * other.real - this->imag * other.imag;
	double i = this->real * other.imag + this->imag * other.real;
	return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) {
	double r = (this->real * other.real + this->imag * other.imag) / ((other.real * other.real) + (other.imag * other.imag));
	double i = (this->imag * other.real - this->real * other.imag) / ((other.real * other.real) + (other.imag * other.imag));
	return Complex(r, i);
}


bool is_integer(double x) {
	return (x == (int)x);
}

void Complex::print() {



	if (this->imag >= 0)
	{
		if (is_integer((int)(this->real * 10))) {
			cout << ((int)(this->real * 10)) / 10.0 << " + ";
		}
		else {
			cout << fixed;
			cout.precision(1);

			cout << ((int)(this->real * 10)) / 10.0 << " + ";

			cout << fixed;
			cout.precision(0);
		}

		if (is_integer((int)(this->real * 10))) {
			cout << ((int)(this->imag * 10)) / 10.0 << 'i';
		}
		else {
			cout << fixed;
			cout.precision(1);

			cout << ((int)(this->imag * 10)) / 10.0 << 'i';

			cout << fixed;
			cout.precision(0);
		}


	}
	else
	{
		if (is_integer((int)(this->real * 10))) {
			cout << ((int)(this->real * 10)) / 10.0 << " - ";
		}
		else {
			cout << fixed;
			cout.precision(1);

			cout << ((int)(this->real * 10)) / 10.0 << " - ";

			cout << fixed;
			cout.precision(0);
		}

		if (is_integer((int)(this->real * 10))) {
			cout << -((int)(this->imag * 10)) / 10.0 << 'i';
		}
		else {
			cout << fixed;
			cout.precision(1);

			cout << -((int)(this->imag * 10)) / 10.0 << 'i';

			cout << fixed;
			cout.precision(0);
		}

	}
}

int main() {

	// Implement your main function

	double real, imag;

	cin >> real >> imag;
	Complex c1(real, imag);

	cin >> real >> imag;
	Complex c2(real, imag);

	cout << "Addition result: ";
	(c1 + c2).print();
	cout << endl;

	cout << "Subtraction result: ";
	(c1 - c2).print();
	cout << endl;

	cout << "Multiplication result: ";
	(c1 * c2).print();
	cout << endl;

	cout << "Division result: ";
	(c1 / c2).print();
	cout << endl;

	return 0;
}
