#include<iostream>

class Zombie {
	int speed_;
	int x_, y_, z_;

public:

	Zombie() {
		this->speed_ = 5;
		this->x_ = 0;
		this->y_ = 0;
		this->z_= 0;
		std::cout << "\ndefault constructor called...\n";
	}

	Zombie(int speed, int x, int y, int z) {
		this->speed_ = speed;
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	}
	
	// The destructor is called automatically by the compiler when the object goes out of scope.
	~Zombie() {
		// destructors does not have any parameters
		std::cout << "\ndestructor called...\n";
	}

	int GetSpeed() { return speed_; }
	int GetX() { return x_; }
	int GetY() { return y_; }
	int GetZ() { return z_; }
};

int main() {

	Zombie* zombie = new Zombie(50,2,3,4);
	std::cout << "Speed: " << zombie->GetSpeed() << "\n x: "<< zombie->GetX() << " y: "<< zombie->GetY() << " z: " << zombie->GetZ();
	
	if( zombie )
		Zombie izombie;		// Destructor is called as soon as if scope is gone
	Zombie izombies[5];

	std::cin.get();
}