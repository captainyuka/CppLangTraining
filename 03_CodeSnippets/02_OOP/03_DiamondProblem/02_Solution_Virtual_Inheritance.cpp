#include<iostream>

class Animal {
public:
	int age;

	Animal() {
		std::cout << "Animal Constructed\n";
	}
};

/*
 *   An inheritance relationship declared using keyword virtual between 
 * classes Derived1 and Derived2 that inherits from class Base means that 
 * another class Derived3 that inherits from Derived1 and Derived2 still 
 * results in the creation of only one instance of Base during instantiation of type Derived3 .
 */

class Mammal : public virtual Animal {

};

class Bird : public virtual Animal {

};

class Reptile : public virtual Animal {

};

class Platypus final : public Mammal, public Bird, public Reptile {
public:
	Platypus() {
		std::cout << "Platypus Constructed\n";
	}
};
int main() {
	Platypus p;		// Only one animal constructed
	p.age = 5;		// No problem	

}