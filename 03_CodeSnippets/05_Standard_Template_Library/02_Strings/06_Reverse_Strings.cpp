#include<iostream>
#include<algorithm>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	std::string sample_str("Mustafa Katipoglu");
	std::cout << "Original String: " << sample_str << "\n\n";

	std::reverse(sample_str.begin(), sample_str.end());
	std::cout << "After reversal: " << sample_str << "\n\n";

	std::reverse(sample_str.begin() + 10, sample_str.end());
	std::cout << "After substring reversal: " << sample_str << '\n';
	
}