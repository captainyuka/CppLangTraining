#include<iostream>
#include<string>
#include<string.h>

// To ensure deep copies, as with the copy constructor, 
// you need to specify an accompanying copy assignment operator

class MyString {
public:
	MyString(const char* init) {
		if (init != nullptr) {
			auto len = strlen(init) + 1;
			buffer_ = new char[ len ];
			strcpy_s(buffer_, len * sizeof(char), init);
		}
		else
			buffer_ = nullptr;
	}

	MyString(const MyString& copy_source);			  // Copy Constructor
	MyString& operator= (const MyString& copy_source);// Copy Assignment Operator

	const char& operator[] (int index) const {
		if (index >= 0 && index < GetLength())
			return buffer_[index];
	}

	operator const char* () {
		return buffer_;
	}

	~MyString() {
		delete[] buffer_;
	}


	char* GetBuffer() const {
		return buffer_;
	}

	int GetLength() const{
		return strlen(buffer_);
	}


private:
	char* buffer_;
};

MyString& MyString::operator=(const MyString& copy_source) {	// Copy Assignment Operator
	char* source_buffer = copy_source.GetBuffer();
	if ( (this != &copy_source) && ( source_buffer != nullptr) ) {
	
		if (buffer_ != nullptr)
			delete[] buffer_;
	
		// ensure deep copy by first allocating own buffer
		buffer_ = new char[strlen(source_buffer) + 1];
		strcpy_s(buffer_, (strlen( source_buffer ) + 1) * sizeof(char), source_buffer);
	}

	return *this;
}

MyString::MyString(const MyString& copy_source) {					// Copy Constructor
	const char* str = copy_source.GetBuffer();
	if (str != nullptr) {
		auto len = strlen(str) + 1;
		buffer_ = new char[len];
		strcpy_s(buffer_, len * sizeof(char), str);
	}
	else
		buffer_ = nullptr;
}

int main() {
	std::cout << "Type a statement: ";
	std::string str_in;
	std::getline(std::cin, str_in);

	MyString you_said(str_in.c_str());
	
	for (auto i = 0; i < you_said.GetLength(); ++i)
		std::cout << you_said[i] << ' ';
	std::cout << '\n';

//	you_said[2] = 'b';	// error, can not assign to a const variable
   // By using const you are protecting internal member MyString::buffer_ from direct modifications from the outside via operator [] .
}


