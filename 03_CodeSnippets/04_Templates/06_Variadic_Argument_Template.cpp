#include<iostream>

/* Variadic Templates */

template<typename Res, typename ValType>
void Sum(Res& result, ValType& val) {
	result = result + val;
}

template<typename Res, typename First, typename... Rest>
void Sum(Res& result, First val1, Rest... val_n) {
	result = result + val1;
	return Sum(result, val_n...);
}

int main() {
	double d_result = 0;
	Sum(d_result, 3.14,	4.56, 1.11);
	std::cout << "d_result = " << d_result << '\n';

	std::string str;
	Sum(str, "Hello ", "World", "!");
	std::cout << "str = " << str << '\n';

}
