#include<iostream>

// Examples of Private Inheritance in real world

// Mammal 'Has a' Heart
// Car 'Has a' Motor
// Pen 'Has a' Nib
 
class Motor {
public:
	void SwitchIgnition() {
		std::cout << "Ignition On\n";
	}

	void PumpFuel() {
		std::cout << "Fuel in cyclinders\n";
	}

	void FireCyclinders() {
		std::cout << "Vrooom\n";
	}
};

class Car : private Motor {
public:
	void Move() {
		SwitchIgnition();
		PumpFuel();
		FireCyclinders();
	}
};

int main() {
	Car dreamCar;
	dreamCar.Move();
}