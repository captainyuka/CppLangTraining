#include<iostream>

class Animal {
public: 
	int legs = 4;

	void run() {
		std::cout << "Animal is running\n";
	}
	
	void speak() {
		std::cout << "Animal is speaking\n";
	}

protected:
	void f() {
		std::cout << "Protected method is in play...";
	}
};

class Cat : Animal {
	// Private Inheritance Mode

	// All inherited members becomes private
};

class Dog : public Animal {
	// Public Inheritance Mode
	
	// Public inherited members becomes public
	// Protected inherited members protected
};

class Bird : protected Animal {
	// Protected Inheritance Mode

	// All inherited methods becomes protected
};

int main() {
	Animal animal;
	Cat kitty;
	
	animal.speak();
	//	kitty.speak(); private methods can not be accessed.

	Dog puppy;
	puppy.speak();
	puppy.run();
	
	Bird fluppy;
	// Bird does not have any public methods

	std::cin.get();
}