#include<iostream>

int main() {
	int original = 21;
	std::cout << "original: " << original << "\t\t &original: " << &original << '\n';
	
	int& alias_to_original = original;
	std::cout << "alias_to_original: " << alias_to_original << "\t &alias_to_original : " << &alias_to_original << '\n'; 
	
	int& another_reference = alias_to_original;
	std::cout << "another_reference: " << another_reference << "\t &another_reference : " << &another_reference << '\n';
}

