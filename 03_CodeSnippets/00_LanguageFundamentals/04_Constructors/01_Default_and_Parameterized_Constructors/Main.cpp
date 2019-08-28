#include<iostream>

class Zombie {
	int speed_;
	int x_, y_, z_;

public:

	// A default constructor is so important for initialization of object members, 
	//   that even if we do not define a constructor explicitly, the compiler will provide a default constructor implicitly.

	Zombie() {
		this->speed_ = 5;
		this->x_ = 0;
		this->y_ = 0;
		this->z_= 0;
		std::cout << "\ndefault constructor called...\n";
	}

	// if we haven't defined default constructor, and compiler will not provide its default constructor because we have defined other parameterized constructors.
	Zombie(int speed, int x, int y, int z) {
		this->speed_ = speed;
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	}
	

	int GetSpeed() { return speed_; }
	int GetX() { return x_; }
	int GetY() { return y_; }
	int GetZ() { return z_; }
};

int main() {

	Zombie* zombie = new Zombie(50,2,3,4);
	std::cout << "Speed: " << zombie->GetSpeed() << "\n x: "<< zombie->GetX() << " y: "<< zombie->GetY() << " z: " << zombie->GetZ();
	
	std::cin.get();
}