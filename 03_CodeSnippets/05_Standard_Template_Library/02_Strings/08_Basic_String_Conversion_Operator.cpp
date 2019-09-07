#include<iostream>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	std::string str("Traditional string \0 initialization");
	std::cout << "str: " << str << "\t Length: " << str.length() << '\n';

	{
		using namespace std::literals::string_literals;				// operator defined in this namespace
		// Requires Cpp 14
		std::string str2 = "C++14 \0 initialization using string literals"s;
		std::cout << "str2: " << str2 << "\t Length: " << str2.length() << '\n';

		// ""s operator constructs a std::basic_string<t>

	}
}

// Reference:
//   https://en.cppreference.com/w/cpp/string/basic_string/operator%22%22s

// see std::literals::string_view_literals for better performance version