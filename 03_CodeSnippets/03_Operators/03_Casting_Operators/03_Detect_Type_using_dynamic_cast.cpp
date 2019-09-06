#include<iostream>

// The result of a dynamic_cast always needs to be checked for validity.

class Fish {
public:
	virtual void Swim(){
		std::cout << "Fish swims in the water\n";
	}

	virtual ~Fish() {}

};

class Tuna : public Fish {
public:
	void Swim() {
		std::cout << "Tuna swims real fast in the sea\n";
	}

	void BecomeDinner() {
		std::cout << "Tuna became dinner in sushi\n";
	}
};

class Carp : public Fish {
public:
	void Swim() {
		std::cout << "Carp swims real slow in the lake\n";
	}

	void Talk() {
		std::cout << "Carp talked Carp!\n";
	}

};

void DetectFishType(Fish* fish) {
	Tuna* tuna = dynamic_cast<Tuna*>(fish);
	if (tuna) {
		std::cout << "Detected Tuna\n";
		tuna->BecomeDinner();
		fish->Swim();			// Verify the type using Virtual Swim()
		return;
	}

	Carp* carp = dynamic_cast<Carp*>(fish);
	if (carp) {
		std::cout << "Detected Carp\n";
		carp->Talk();
		fish->Swim();			// Verify the type using Virtual Swim()
		return;
	}
}

int main() {
	Carp launch;
	Tuna dinner;
	DetectFishType(&launch);
	std::cout << '\n';
	DetectFishType(&dinner);
}
