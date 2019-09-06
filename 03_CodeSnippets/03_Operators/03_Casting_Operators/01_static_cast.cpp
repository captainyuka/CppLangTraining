#include<iostream>


/*
 *   static_cast is a mechanism that can be used to convert pointers between related
 * types, and perform explicit type conversions for standard data types that would otherwise
 * happen automatically or implicitly.
*/

class Base {

};

class Derived : public Base {

};

int main() {

	/* static_cast Use Case 1 : Upcasting - Downcasting */

	Derived objDerived;
	Base* obj_base = &objDerived;			// Upcasting , can be done without explicit casting
	obj_base = static_cast<Base*>(&objDerived);		// To take attention of reader, explicit upcasting can be done

	// Downcasting can not be done without usage of casting operators
	// Derived* ptr_to_obj_base = obj_base;	// error
	Derived* ptr_to_obj_base = static_cast<Derived*>(obj_base);			// Works great

	// note that static_cast verifies only that the pointer types are related. 
	// It does not perform any runtime checks.
	Base* real_object_base = new Base();
	Derived* obj_derived = static_cast<Derived*>(real_object_base);		// still no error .s
	// results in unexpected behaviour at runtime since obj_derived partially class Derives


	/* static_cast Use Case 2 : Explicit Casts */
	
	double pi = 3.1415;
	int num = static_cast<int>(pi);		// Also used to make Explicit cast
}
