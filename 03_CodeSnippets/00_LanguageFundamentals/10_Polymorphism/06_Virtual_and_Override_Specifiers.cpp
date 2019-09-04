#include<iostream>

// Use of keyword virtual means that
// the compiler ensures that any overriding variant
// of the requested base class method is invoked.

class Animal {
	int x_, y_;
public:
	Animal(int x = 0, int y = 0) : x_(x), y_(y) {}

	virtual	void run() {				// By marking virtual we allow dynamic binding and the ability to be overriden
		std::cout << "Running";
	}

};

class Rabbit : public Animal{
public:
	void run() override {				// override keyword not compulsory but should be used
		std::cout << "Rabbit is running";
	}
};

int main(){

	Animal* ptr ;
	Rabbit* r = new Rabbit;
	ptr = r;

	ptr->run();			// calls the overriden run method
	
	delete r;
	std::cin.get();
}

