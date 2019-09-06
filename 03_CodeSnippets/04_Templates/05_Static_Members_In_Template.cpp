#include<iostream>

template<typename T>
class TestStatic {
public:
	static int static_val;
};

// Static member initialization

template<typename T> int TestStatic<T>::static_val;

int main() {
	TestStatic<int>	int_instance;
	TestStatic<double> double_instance;

	int_instance.static_val = 2050;
	double_instance.static_val = 2050;

	std::cout << "Setting static_val to 2019 for int_instance\n";
	int_instance.static_val = 2019;
	std::cout << "int_instance static_val: " << int_instance.static_val << '\n';
	std::cout << "double_instance static_val: " << double_instance.static_val << '\n';
	
	std::cout << '\n';
	
	std::cout << "Setting static_val to 2020 for double_instance\n";
	double_instance.static_val = 2020;
	std::cout << "int_instance static_val: " << int_instance.static_val << '\n';
	std::cout << "double_instance static_val: " << double_instance.static_val << '\n';
	
	/* Output:
		Setting static_val to 2019 for int_instance
		int_instance static_val: 2019
		double_instance static_val: 2050

		Setting static_val to 2020 for double_instance
		int_instance static_val: 2019
		double_instance static_val: 2020
	*/

	// Thus, the compiler ensured that the behavior of the static variable remains
	//	intact for the instantiation of the template class for a particular type.
}
