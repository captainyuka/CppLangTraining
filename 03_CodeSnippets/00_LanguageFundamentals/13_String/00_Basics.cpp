#include<iostream>
#include<string>


int main() {
	std::string greetings("Hello World!");
	std::cout << greetings << '\n';

	std::cout << "Input Text: ";
	std::string input;
	std::getline(std::cin, input);

	std::cout << "Text for concatenation: ";
	std::string second_input;
	std::getline(std::cin, second_input);

	std::cout << "Concatenated String: \n";
	std::string concat = input + " " + second_input;
	std::cout << concat << '\n';

	std::string copy_concat = concat;
	std::cout << "Copy of concatenated string: \n";
	std::cout << concat << '\n';	
	
	std::cout << "Length of copy_concat: " << copy_concat.length();
}


