#include<iostream>


enum Size {
	S, M, L, X, XL, XXL			// S = 0, M = 1 ... 
};

enum Length {
	Short = 0, Middle = 2, Tall		// Tall gets value 3
};

// Enums by default 32bit integers
enum Len : unsigned char{  // We can use 8bit by using this style
	N, R, Z
};

int main(){

	Size s = Size::M;
	if (s != Size::L && s == M)		// We can represent in both ways
		std::cout << "Yeap s is M\n";
	
	Length l = Length::Tall;

	Len len = Len::N;

	std::cout << "Sizeof Len " << sizeof len << " Bytes\n";
	std::cout << "Sizeof l " << sizeof l << " Bytes\n";



	std::cin.get();
}
