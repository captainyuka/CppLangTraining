#include<iostream>


/*
 *	dynamic_cast executes the cast at runtime—that is, at application execution time. 
 * The result of a dynamic_cast operation can be checked 
 * to see whether the attempt at casting succeeded.

 * dynamic_cast returns NULL on failure, and throws std::bad_cast when casting references. 
 * It is a compile-time error to attempt to cast objects with dynamic_cast eg, with dynamic_cast<Derived>(base)
 */

class Base {
	virtual void doSomething() = 0;
};

class Derived : public Base {
public:
	void doSomething() {
		std::cout << "Do Something, what are u waiting for?\n";
	}
};

int main() {

	Base* obj_base = new Derived();
	Derived* obj_der = dynamic_cast<Derived*>(obj_base);
	if (obj_der)			// check for success of the cast
		obj_der->doSomething();

}
