#include<iostream>

class Human {
	friend void DisplayAge(const Human&);
	std::string name_ = "Anonymous";
	int age_;

public:
	Human(int age):age_(age) {}
	std::string GetName() {
		return name_;
	}
	void SetName(std::string name) {
		name_ = name;
	}
};

void DisplayAge(const Human& person){
	std::cout << person.age_ << '\n';
}

int main() {
	Human x(10);
	DisplayAge(x);	// Accessing private member via friend function
}

