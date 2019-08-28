#include<iostream>

/**
 * Data members are all lowercase, with underscores between words additionally have trailing underscores. 
 */

class Player {

public:
	int speed_, x_, y_, z_;
	const char* name_;

	void setName(const char* name_) {
		this->name_ = name_;
	}

	void setSpeed(int speed_) {
		this->speed_ = speed_;
	}

	void Move(int x_, int y_, int z_) {
		this->x_ = x_;
		this->y_ = y_;
		this->z_ = z_;
	}

	void toString() {
		std::cout << "name: " << name_ << "\nspeed: " << speed_ << "\nx: " << x_ << " y: " << y_ << " z: " << z_ << std::endl;
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