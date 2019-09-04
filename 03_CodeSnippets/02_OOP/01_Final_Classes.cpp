#include<iostream>

class Particle {

};

class Stone final : public Particle {

};

class BlackStone : Stone {
	// Error, can not inherit from final class
};

int main() {
}