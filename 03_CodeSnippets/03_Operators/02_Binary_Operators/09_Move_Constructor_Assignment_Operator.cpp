#include<iostream>
#include<string.h>

/*
 * Move Assignment Operator and Constructor  takes temporary values that will be deleted(rvalues)
 * and moves its resources to the newly created object, 
 * so new object won't allocate new resource but will use the old resource

 * Don't forget to nullify temp variable's slot otherwise when it is destructed, things will go crazy

 * If we will only use reference of this class, no need to have move constructor
 * if we'll use pass value, then this will boost the performance to as close as pass by reference
 *  pass by reference ~ Fastest
 *  pass by value with move assignment-constructor ~ Middle speed
 *  pass by value with no move(with copy constructor, deep copy) ~ slowest

 * If we have and lvalue but we surely know we won't use it anymore and will be deleted after function call
 * we can use this syntax to call move constructor with that lvalue
 * foo(std::move(my_variable));
 * Remeber my_variables internels will be nulled after it has moved, don't try to reuse that variable ever.

*/


class MyString {
public:
	MyString(const char* init) {		// Overloaded Costructor
		std::cout << "Constructor called for " << init << '\n';
		if (init != nullptr) {
			auto len = strlen(init) + 1;
			buffer_ = new char[len];
			strcpy_s(buffer_,len * sizeof(char),init);
		}
		else
			buffer_ = nullptr;
	}

	// && means r-value reference
	MyString(MyString&& move_src) {				// Move Constructor, takes R-value reference
		std::cout << "Move constructor moves: " << move_src.GetBuffer() << '\n';
		if (move_src.GetBuffer() != nullptr) {
			buffer_ = move_src.GetBuffer();						// take ownership of buffer, 'move'
			move_src.SetBuffer(nullptr);		// free move source
		}
	}
	
	MyString& operator=(MyString&& move_src) {	// Move Assignment Operator
		std::cout << "Move assignment operator moves: " << move_src.GetBuffer() << '\n';
		if ( (move_src.GetBuffer() != nullptr) && (this != &move_src) ) {
			this->SetBuffer( move_src.GetBuffer() );
			move_src.SetBuffer(nullptr);		// free move source
		}

		return *this;
	}

	MyString(const MyString& copy_src) {		// Copy Constructor
		
		std::cout << "Copy constructor copies: " << copy_src.GetBuffer() << '\n';
		if (copy_src.GetBuffer() != nullptr) {
			auto len = strlen(copy_src.GetBuffer()) + 1;
			buffer_ = new char[len];
			strcpy_s(buffer_, len, copy_src.GetBuffer());
		}
		else
			buffer_ = nullptr;
			
	}

	MyString& operator= (const MyString& copy_src) {					// Copy Assignment Operator
		
		std::cout << "Move assignment operator copies: " << copy_src.GetBuffer() << '\n';
		if ( (copy_src.GetBuffer() != nullptr) && (this != &copy_src) ) {
			auto len = strlen(copy_src.GetBuffer()) + 1;
			char* temp_buffer = new char[ len ];
			strcpy_s(temp_buffer, len, copy_src.GetBuffer());
			this->SetBuffer(temp_buffer);
			temp_buffer = nullptr;
		}
	
		return *this;
	}

	~MyString() {		// Destructor
		delete[] buffer_;
	}

	operator const char* () {		// conversion operator
		return buffer_;
	}

	auto GetLength() {
		return strlen(buffer_);
	}

	MyString operator+(const MyString& add_this) {
		std::cout << "operator+ called: \n";
		
		MyString new_str;

		if (add_this.GetBuffer() != nullptr) {
			auto len = strlen(add_this.GetBuffer()) + strlen(buffer_) + 1;
			char* temp = new char[len];
 			strcpy_s(temp, len ,buffer_);
			strcat_s(temp, len ,add_this.GetBuffer());
			new_str.SetBuffer(temp);
			temp = nullptr;
		}

		return new_str;
	}


	char* GetBuffer() const{
		return buffer_;
	}

	void SetBuffer(char* str) {
		buffer_ = str;			// assign new one
	}

private:
	char* buffer_;

	MyString(): buffer_(nullptr){		// Private default Constructor
		std::cout << "Default Constructor Called\n";
	}
};


int main() {
	MyString hello("Hello");
	MyString world("World");
	MyString cpp(" of C++");

	MyString say_hello("overwrite this");
	say_hello = hello + world + cpp;
}

