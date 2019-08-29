#include<iostream>

class Animal {
public: 
	int legs_ = 4;

	Animal() {
		std::cout << "Hi From Animal Constructor...\n";
	}

	Animal(int legs) {
		this->legs_ = legs;
		std::cout << "Hi From Parameterized Animal Constructor...\n";
	}

	void move() {
		std::cout << "Animal is moving\n";
	}
};

class TestSubject {
public:
	int id = -1;
	int experimentRecordCount = 0;
	
	TestSubject() {
		std::cout << "Hi From TestSubject Constructor...\n";
	}
};


class LabRat : public Animal, public TestSubject {
public:
	LabRat() {
		std::cout << "Hi From LabRat Constructor...\n";
	}
};

int main() {

	LabRat x;

	std::cin.get();
}