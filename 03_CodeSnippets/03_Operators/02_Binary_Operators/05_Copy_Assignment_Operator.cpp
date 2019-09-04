#include<iostream>
#include<string.h>

// To ensure deep copies, as with the copy constructor, 
// you need to specify an accompanying copy assignment operator

class MyString {
public:
	MyString(const char* init) {
		if (init != nullptr) {
			auto len = strlen(init) + 1;
			buffer_ = new char[ len];
			strcpy_s(buffer_, len * sizeof(char), init);
		}
		else
			buffer_ = nullptr;
	}

	MyString& operator= (const MyString& copy_source) {		// Copy Assignment Operator
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

	operator const char* () {
		return buffer_;
	}

	~MyString() {
		delete[] buffer_;
	}


	char* GetBuffer() const {
		return buffer_;
	}


private:
	char* buffer_;
};

int main() {
	
	MyString name("Mustafa");
	MyString surname("Katipoglu");

	std::cout << "Before Assignment: " << "\tName: "<< name << "\tSurname: " << surname << '\n';
	
	name = surname;

	std::cout << "After Assignment: " << "\tName: "<< name << "\tSurname: " << surname << '\n';

}


