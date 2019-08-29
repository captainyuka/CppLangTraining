#include<iostream>

class Animal {
	int legs_ = 4;

public: 
	bool operator == (const Animal& other) {
		if (this->legs_ == other.legs_)
			return true;
		return false;
	}
};
/* Keep in Mind !
 * Precedence and Associativity of an operator cannot be changed.
 * Arity (numbers of Operands) cannot be changed. Unary operator remains unary, binary remains binary etc.
 * No new operators can be created, only existing operators can be overloaded.
 * Cannot redefine the meaning of a procedure. You cannot change how integers are added.
 */

int main(){

	Animal x, y;

	if (x == y)
		std::cout << "They are equal...\n";

	std::cin.get();
}