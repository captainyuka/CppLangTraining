#include<iostream>

// unions can not inherit
union User{		// by default members public
	int index;
	char alphabet;
	User() {}
	~User() {}
};

struct ComplexType {
	enum Choice {
		INDEX, ALPHABET
	} choice_;

	User user;
};

void printID(const ComplexType& x) {
	std::cout << '\n';
	switch ( x.choice_ ) {
	case ComplexType::INDEX:
		std::cout << "User ID: " << x.user.index;
		break;
	case ComplexType::ALPHABET:
		std::cout << "User ID: " << x.user.alphabet;
		break;
	}
	std::cout << '\n';
}

int main() {
	User user;
	user.index = 1;
	std::cout << "Size: " << sizeof(user) << " Bytes\n";
	
	std::cout << '\n';	

	std::cout << "Valid Index: " << user.index << '\n';
	std::cout << "Invalid Alphabet: " << user.alphabet << '\n';
	
	std::cout << '\n';	

	user.alphabet = 'x';
	std::cout << "Invalid Index: " << user.index << '\n';
	std::cout << "Valid Alphabet: " << user.alphabet << '\n';
	
	ComplexType t;
	t.choice_ = ComplexType::INDEX;
	t.user.index = 82;
	printID(t);
	
}

