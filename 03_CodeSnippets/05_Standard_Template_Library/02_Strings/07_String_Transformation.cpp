#include<iostream>
#include<algorithm>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int MyOwnToUpper(int c) {
	static int difference = 'a' - 'A';
	return c - difference;
}

int MyOwnToLower(int c) {
	static int difference = 'a' - 'A';
	return c + difference;
}

int main() {
	std::cout << "Please give a string for case conversion:\n";
	std::string str;
	std::getline(std::cin, str);
	std::cout << '\n';
	
	// Using Standard toupper and tolower

	std::transform(str.begin(), str.end(), str.begin(), std::toupper);
	std::cout << str << "\n\n";

	std::transform(str.begin(), str.end(), str.begin(), std::tolower);
	std::cout << str << "\n\n";

	// Using My toupper and tolower

	std::transform(str.begin(), str.end(), str.begin(), MyOwnToUpper);
	std::cout << str << "\n\n";

	std::transform(str.begin(), str.end(), str.begin(), MyOwnToLower);
	std::cout << str << "\n\n";
}