#include<iostream>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	const char* str = "Hello World!";
	std::string my_std_str(str);				// Create string with const char*
	print(my_std_str);

	std::string my_alt_std_str("Hello World");	// Create string with const char*
	print(my_alt_std_str);

	std::string my_copy_std_str(my_std_str);	// Create string with another string
	print(my_copy_std_str);

	// Be careful, this constructor take c style string, const char*
	std::string first_n_char_str(str, 2);		// string with first 2 character of str
	print(first_n_char_str);

	std::string str_repeated_chars(10, 'a');	// fast way to repeat a char in a string : aaaaaaaaaa
	print(str_repeated_chars);
}

