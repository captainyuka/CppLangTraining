#include<iostream>		
#include<vector>
#include<list>

template<class T>
void printList(std::list<T>& t) {
	if (t.empty()) {
		std::cout << "List is totally empty...\n";
		return;
	}

	for (auto i = t.cbegin(); i != t.cend(); ++i)
		std::cout << *i << ' ';
	std::cout << '\n';
}

int main() {
	
	std::list<int> list;						// Empty List
	printList(list);
	
	std::list<int> list1(10);					// List of 10 elements
	printList(list1);

	std::list<int> list2 = {1,3,5,7,9};			// Initialize using C++11 initializer list
	printList(list2);

	std::list<int> list3(list2);				// List which contains elements of list2
	printList(list3);

	std::list<int> list4(10, 99);				// List of 10 elements with each 99 value
	printList(list4);

	std::vector<int> vector(5, 2020);
	std::list<int> list5(vector.cbegin(), vector.cbegin()+3);	// List of First 3 elements of vector
	printList(list5);
}