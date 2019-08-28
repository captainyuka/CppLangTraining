#include<iostream>

class Player {

public:
	int speed, x, y, z;
	const char* name;

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

	std::cin.get();
 }