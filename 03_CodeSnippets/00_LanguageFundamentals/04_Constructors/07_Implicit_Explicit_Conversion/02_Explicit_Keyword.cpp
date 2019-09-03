#include<iostream>

class Human {
	std::string name_ = "Anonymous";
	int age_;
public:
	// explicit constructor blocks implicit conversions
	explicit Human(int age):age_(age) {}
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
	Human kid(10);			// convert an integer to a human
	kid.SetName("Rabia");
	DoSomething(kid);
	
	Human anotherKid = Human(11);	// explicit coversion
	anotherKid.SetName("Eyup");
	DoSomething(anotherKid);

//	Human somebody = 11;		// try implicit coversion, Error...
//	DoSomething(20);			// try implicit conversion, Error
}
