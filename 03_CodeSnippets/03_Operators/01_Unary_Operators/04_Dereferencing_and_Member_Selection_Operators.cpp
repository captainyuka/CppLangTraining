#include<iostream>
#include<memory>		// to use std::unique_ptr

// Programming Dereference Operator ( * ) and Member Selection Operator(->)

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	void DisplayDate() {
		std::cout << day_ << " / " << month_ << " / " << year_ << '\n';
	}

private:
	int day_, month_, year_;
};

int main() {
	// class std::unique_ptr that is smart because it implements operator ( * ) and	operator ( -> )
	std::unique_ptr<int> smartIntPtr(new int);		
	*smartIntPtr = 42;

	// Use smart pointer type like int*
	std::cout << "Integer value is: " << *smartIntPtr << '\n';
	
	std::unique_ptr<Date> smartDate(new Date(31,3,1908));
	smartDate->DisplayDate();		// like a Date*

}

