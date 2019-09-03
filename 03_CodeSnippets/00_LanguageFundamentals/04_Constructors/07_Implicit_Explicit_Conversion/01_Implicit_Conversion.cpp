#include<iostream>

class Human {
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

void DoSomething(Human person) {
	std::cout << person.GetName() << " did something ...\n";
}

int main() {
	Human kid(10);					// convert an integer to a human
	kid.SetName("Rabia");
	DoSomething(kid);
	
	Human somebodyElse = Human(24); // Explicit coversion
	Human somebody = 15;			// implicit conversion
	DoSomething(20);				// implicitly converts 20 to a human
}

