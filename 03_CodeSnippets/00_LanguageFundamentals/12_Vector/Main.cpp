#include<iostream>
#include<vector>

void printVector(std::vector<int> arr) {

	for (int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << '\n';
	
}

int main() {
	int i,n;
	std::cout << "How many elements would you like to place: \n";
	std::cin >> n;
	
	std::vector<int> dynamicArray(n);
	for (i = 0; i < n; i++) {
		std::cout << "Element " << (i + 1) << ":";
		std::cin >> dynamicArray[i];
	}
	printVector(dynamicArray);
}


