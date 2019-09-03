#include<iostream>
#include<string.h>

class MyString {
public:
	// Copy Constructor
	MyString(const MyString& copySource);

	MyString(const char* str) {
		buffer = nullptr;
		std::cout << "Default constructor, creating new String\n";
		if (str != nullptr) {
			buffer = new char[strlen(str) + 1];
			strcpy_s(buffer, strlen(str) + 1 ,str);
			std::cout << "Buffer points to: " << (unsigned int*)buffer << '\n';
		}
	}

	~MyString() {
		std::cout << "Cleaning up...\n";
		delete[] buffer;
	}

	int GetLength() {
		return strlen(buffer);
	}

	const char* GetString() {
		return buffer;
	}

private:
	char* buffer;
};

// Take deep copy
MyString::MyString(const MyString& copySource){
	// Copy constructor is always called when this class passed by value.
	buffer = nullptr;
	std::cout << "Copying...\n";
	if (copySource.buffer != nullptr) {
		// Allocate own buffer
		buffer = new char[strlen(copySource.buffer) + 1];
		strcpy_s(buffer, strlen(copySource.buffer) + 1,copySource.buffer);
		std::cout << "Buffer points to: " << (unsigned int*)buffer << '\n';
	}
}

void UseMyStr(MyString my_string) {
	std::cout << "buffer contains " << my_string.GetLength() << " characters\n";
}

int main() {
	MyString str("Hello from MyString class");
	UseMyStr(str);
}


