#include<iostream>

/*
 * Since virtual copy constructors is not possible in c++
 * we use virtual function Clone as a workaround
 * Sample code demonstrates virtual copy constructors via virtual function Fish::Clone()
*/

class Fish {
public:
	virtual Fish* Clone() = 0;
	virtual void Swim() = 0;
	virtual ~Fish() {}
};

class Tuna : public Fish {
public:
	Fish* Clone() override {
		return new Tuna(*this);
	}

	void Swim() override final {
		std::cout << "Tuna swims fast in the sea\n";
	}
};

class BluefinTuna : public Tuna {
	Fish* Clone() override {
		return new BluefinTuna(*this);
	}
	// can not override Swim since it is final
};

class Carp : public Fish {
	Fish* Clone() override {
		return new Carp(*this);
	}

	void Swim() override final {
		std::cout << "Carp swims slow in the lake\n";
	}
};

int main() {
	const int kArraySize = 4;
	
	Fish* myFishes[kArraySize] = { nullptr };
	myFishes[0] = new Tuna();
	myFishes[1] = new Carp();
	myFishes[2] = new BluefinTuna();
	myFishes[3] = new Carp();

	Fish* myNewfishes[kArraySize];
	for (auto i = 0; i < kArraySize; ++i)			
		myNewfishes[i] = myFishes[i]->Clone();
	
	std::cout << "\n myNewfishes starts to swim...\n";

	for (auto i = 0; i < kArraySize; ++i)			// Invoke virtual method to check
		myNewfishes[i]->Swim();
	
	for (auto i = 0; i < kArraySize; ++i) {			// Memory Cleanup
		delete myNewfishes[i];
		delete myFishes[i];
	}
}

