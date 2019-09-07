#include<iostream>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	std::string str("Hello String");

	// Array Style
	for (auto i = 0; i < str.length(); ++i)
		std::cout << str[i];
	std::cout << '\n';

	// Iterator Style
	std::string::iterator char_locator = str.begin();		// const iterator or iterator depending on str state
	for (; char_locator != str.end(); ++char_locator)		
		std::cout << *char_locator;
	std::cout << '\n';

	// Strict Constant Iterator
	std::string::const_iterator c_iterator = str.cbegin();
	for (; c_iterator != str.cend(); ++c_iterator)
		std::cout << *c_iterator;
	std::cout << '\n';

	// Alternative Iterator Style
	for (auto i = str.begin(); i != str.end(); ++i)
		std::cout << *i;
	std::cout << '\n';

	// Access Content
	std::cout << str.c_str() << '\n';
	
}

/*
 *	begin will return an iterator or a const_iterator depending on the const-qualification of the object it is called on.
 *	cbegin will return a const_iterator unconditionally.
*/

