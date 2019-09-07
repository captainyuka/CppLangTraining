#include<iostream>
#include<vector>

template<class T>
void printVector(std::vector<T>& t, std::string& additional_note) {		// iterators
	std::cout << additional_note << ' ';
	for (auto iterator = t.cbegin(); iterator != t.cend(); ++iterator)
		std::cout << *iterator << ' ';
	std::cout << '\n';
}

template<typename T>		
void printVector(std::vector<T>& t, std::string&& additional_note) {	// subscript operator
	std::cout << additional_note << ' ';
	// If one tries to access element outside of array, behaviour undefined, use at() function
	for (auto i = 0; i < t.size(); ++i)
		std::cout << t[i] << ' ';
	std::cout << '\n';
}

template<class T>		// Standard libraries prefers class when declaring generic type
void printVector(std::vector<T>& t, const char* additional_note) {		// Member at() function
	std::cout << additional_note << ' ';
	// Prefer at() call over subscript operator[] since it checks boundaries and throws exception
	for (auto i = 0; i < t.size(); ++i)
		std::cout << t.at(i) << ' ';
	std::cout << '\n';
}

template<class T>
void printVector(std::vector<T>& t, std::string* additional_note) {
	std::cout << *additional_note << ' ';

	std::vector<int>::const_iterator iterator = t.cbegin();				// Pointer Semantics
	while (iterator != t.cend()) {
		auto index = std::distance(t.cbegin(), iterator);
		std::cout << *iterator << ' ';
		iterator++;
	}

	std::cout << '\n';
}

int main() {
	std::vector<int> arr(5, 25);
	std::string str("arr:");
	printVector(arr, str);
	printVector(arr, "Access using at():");
	printVector(arr, std::string("Access using subscript operator[]:"));
	printVector(arr, &str);
}