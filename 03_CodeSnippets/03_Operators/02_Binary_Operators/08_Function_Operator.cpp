#include<iostream>

class Display {
public:
	void operator () (std::string input) const {		// Function Operator
		std::cout << input << '\n';
	}
};

int main() {
	Display display_func_obj;

	display_func_obj("Looks just like a function right call right ? ");
	display_func_obj.operator()("Same as the upper call");

}


