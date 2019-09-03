#include<iostream>
#include<string.h>

class MyString {

public:
	MyString(const char* str);
	~MyString();
	int GetLength();
	const char* GetString();

private:
	char* buffer;
	// Copy is not allowed. 
	MyString(const MyString& copySource);		// private copy constructor
	MyString& operator= (const MyString&);		// private copy assignment operator

	//  There is no need for implementation of the private copy constructor or assignment operator.
};


void UseMyStr(MyString my_string) {
	std::cout << "buffer contains " << my_string.GetLength() << " characters\n";
}

int main() {
	MyString str("Hello from MyString class");
	UseMyStr(str);		// Can not pass by value since we are not allowed to copy...
}

MyString::MyString(const char* str) {
	buffer = nullptr;
	std::cout << "Default constructor, creating new String\n";
	if (str != nullptr) {
		buffer = new char[strlen(str) + 1];
		strcpy_s(buffer, strlen(str) + 1 ,str);
		std::cout << "Buffer points to: " << (unsigned int*)buffer << '\n';
	}
}

MyString::~MyString() {
	std::cout << "Cleaning up...\n";
	delete[] buffer;
}

int MyString::GetLength() {
	return strlen(buffer);
}

const char* MyString::GetString() {
	return buffer;
}


