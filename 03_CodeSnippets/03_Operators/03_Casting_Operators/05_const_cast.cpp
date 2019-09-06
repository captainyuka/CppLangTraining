#include<iostream>

/*
 * Note that using const_cast to invoke non-const functions should be a last resort.
	In general, keep in mind that using const_cast to modify a const object can also
	result in undefined behavior.
*/

class Fish {
public:
	void Display() {
		std::cout << "Fish...\n";
	}
};

void DisplayData(const Fish* fish){
	// fish->Display();		// Error, can not cash const Fish to Fish
	Fish* temp = const_cast<Fish*>(fish);
	temp->Display();
}

int main() {
	Fish f;
	DisplayData(&f);
}
