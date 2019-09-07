#include<iostream>			
#include<vector>

template<class T>	
void printVector(std::vector<T>& t, std::string additional_note) {		
	std::cout << additional_note << ' ';
	for (auto i = 0; i < t.size(); ++i)
		std::cout << t.at(i) << ' ';
}

template <class T>
void printState(std::vector<T>& arr, std::string additional_note = "arr:") {
	printVector(arr, additional_note);
	std::cout << "\tSize: " << arr.size() << "\tCapacity: " << arr.capacity() << "\n\n";
}

int main() {
	std::vector<int> arr = {1,2,3,4,5,6,7,8,9,10};
	printState(arr);
	
	arr.push_back(11);
	printState(arr);

	arr.pop_back();
	printState(arr);

	arr.clear();
	printState(arr);

	arr.insert(arr.begin(),20,0);		// insert 20 piece value 0
	printState(arr);

	// Start a new vector with initial capacity of 5
	arr = std::vector<int>(5);		
	printState(arr);
	
	arr.reserve(25);		// increase capacity
	printState(arr);
}