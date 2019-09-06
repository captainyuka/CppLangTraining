# reinterpret_cast

 * reinterpret_cast allows the programmer to cast one object type to another, 
    regardless of whether or not the types are related

 * This cast actually forces the compiler to accept situations 
    that static_cast would normally not permit.
 
 * It finds usage in certain low-level applications (such as drivers, for
	example) where data needs to be converted to a simple type that an API—Application
	Program Interface—can accept (for example, some OS-level APIs require data to be sent
	as a BYTE array, that is, unsigned char* )

````c++
	SomeClass* object = new SomeClass();
	// Need to send the object as a byte-stream...
	unsigned char* bytesFoAPI = reinterpret_cast<unsigned char*>(object);
````

* The cast used in the preceding code has not changed the binary representation of the
	source object and has effectively cheated the compiler into allowing the programmer
	to peek into individual bytes contained by an object of type SomeClass .
