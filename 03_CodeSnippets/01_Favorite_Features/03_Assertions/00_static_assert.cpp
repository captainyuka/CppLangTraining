#include<iostream>

template<typename T>
class EverythingButInt {
public:
	EverythingButInt() {
		static_assert(sizeof(T) != sizeof(int), "No int Please!");
	}
};

int main() {
	EverythingButInt<int> test;			// compile time error
}
