#include<iostream>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	std::string hello_str("Hello");
	std::string world_str(" World!");

	// Concatenate Strings with += Operator
	hello_str += world_str;			
	print(hello_str);
	
	// Concatenate Strings with append()
	hello_str.append(world_str);			
	print(hello_str);

	hello_str.append(" Why not append this const* too ?");
	print(hello_str);

	hello_str += " Of course";
	print(hello_str);

		

}