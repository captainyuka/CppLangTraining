#include<iostream>

/*
 * Use a struct only for passive objects that carry data; everything else is a class.
 * Classes has by default private fields and we need to specify explicitly public fields
 * Structs has by default public fields and we need to specify explicitly private fields
 * structs should be used for passive objects that carry data, and may have associated constants, but lack any functionality other than access/setting the data members. The accessing/setting of fields is done by directly accessing the fields rather than through method invocations. Methods should not provide behavior but should only be used to set up the data members, e.g., constructor, destructor, Initialize(), Reset(), Validate().
 * 
 */

class Player {

	int speed, x, y, z;
	const char* name;

public:
	void setName(const char* name) {
		this->name = name;
	}

	void setSpeed(int speed) {
		this->speed = speed;
	}

	void Move(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void toString() {
		std::cout << "name: " << name << "\nspeed: " << speed << "\nx: " << x << " y: " << y << " z: " << z << std::endl;
	}
};

struct Zombie {

private:
	int speed, x, y, z;
	const char* name;

public:

	void setName(const char* name) {
		this->name = name;
	}

	void setSpeed(int speed) {
		this->speed = speed;
	}

	void Move(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void toString() {
		std::cout << "name: " << name << "\nspeed: " << speed << "\nx: " << x << " y: " << y << " z: " << z << std::endl;
	}
};


int main() {
	
	Player agent;
	agent.Move(0,0,0);
	agent.setSpeed(5);
	agent.setName("Navigation Agent");
	agent.toString();

	Zombie zombie;
	zombie.Move(0,0,0);
	zombie.setSpeed(5);
	zombie.setName("Fast Zombie");
	zombie.toString();



	std::cin.get();
 }