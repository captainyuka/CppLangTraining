#include<iostream>

struct Temperature {
	double kelvin_;
	Temperature(long double kelvin) : kelvin_(kelvin) {}
};

// User defined global literal
Temperature operator"" _C(long double celcius) {
	return Temperature(celcius + 273);
}

Temperature operator"" _F(long double fahrenheit) {
	return Temperature( (fahrenheit + 459.67) * 5/9 );
}

int main() {
	Temperature k1 = 25.0_F;
	Temperature k2 = 0.0_C;

	std::cout << "k1: " << k1.kelvin_ << " Kelvin\n";
	std::cout << "k2: " << k2.kelvin_ << " Kelvin\n";
}

