#include<iostream>

class Animal {
public:
	virtual void exist(){
	
	}
};

class Mammal:Animal {
public:
	void exist() override final {
	
	}
};

class Bear :Mammal {
public:
	void exist() override {
		// Error, final method can not be overriden!	
	}
};

int main() {
}