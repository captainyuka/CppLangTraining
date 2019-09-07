#include<iostream>
#include<vector>

template<typename T>
void printVector(std::vector<T> t, std::string additional_note = "") {
	std::cout << additional_note << ' ';
	for (auto i = 0; i < t.size(); ++i)
		std::cout << t[i] << ' ';
	std::cout << '\n';
}

int main() {
	
	std::vector<int> arr;		
	std::vector<int>::const_iterator iterator;
	
	arr.push_back(45);			// insert at the end
	arr.push_back(445);
	arr.push_back(4445);
	printVector(arr, "arr:");

	// push_back preferred over insert since insertion have moving costs

	// insert 25 at the beginning
	arr.insert(arr.begin(), 25);
	printVector(arr, "arr:");

	// insert 2 elements whose value 45 at the end
	arr.insert(arr.end(), 2, 45);
	printVector(arr, "arr:");

	// arr2 new vector contains 2 elements of value 30
	std::vector<int> arr2(2,30);
	printVector(arr2, "arr2:");
	
	// insert all elements of arr2 starting with index 1
	arr.insert(arr.begin() + 1, arr2.begin(), arr2.end() );
	printVector(arr,"arr:");


}