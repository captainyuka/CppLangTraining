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

	// C++11 list initialization
	std::vector<int> arr_1{ 404,303,-1 };		
	printVector(arr_1, "arr1:");

	// Initialize with 10 elements(can grow)
	std::vector<int> arr_2(10);
	printVector(arr_2, "arr_2:");

	// Init with 10 elements each of which has value 101
	std::vector<int> arr_3(10, 101);
	printVector(arr_3, "arr_3:");

	// Init with copy of the contents of arr_3
	std::vector<int> arr_4(arr_3);
	printVector(arr_4, "arr_4:");

	// Init with iterators, first 5 elements of arr_3
	std::vector<int> arr_5(arr_3.cbegin(), arr_3.cbegin() + 5);
	printVector(arr_5, "arr_5:");


}