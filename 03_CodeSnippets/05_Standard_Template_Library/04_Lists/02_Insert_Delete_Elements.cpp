#include<iostream>	
#include<algorithm>
#include<list>

template<class T>
void printContents(const T& container) {	// Generic Print for containers
	if (container.empty()) {
		std::cout << "Container is totally empty...\n";
		return;
	}

	for (auto i = container.cbegin(); i != container.cend(); ++i)
		std::cout << *i << ' ';
	std::cout << '\n';
}

int main() {
	std::list<int> list = {1,3,5,7,9};
	printContents(list);

	/* Inserting Elements*/
	std::cout << "Inserting Elements...\n\n";

	list.push_back(11);					// Insert from back
	list.push_front(-1);				// Inser from front
	printContents(list);

	// insert returns iterator pointing to the newly added element
	list.insert(list.begin(), 2);		// insert from front
	printContents(list);

	list.insert(list.end(), 7);			// insert from back
	printContents(list);

	list.insert(list.begin(), 5, 4 );	// insert 5 elements of value 4 from front
	printContents(list);
	
	list.insert(list.begin(), list.begin(),list.end());		// append whole list to start of itself
	printContents(list);
	
	// Append contents of another_list at the end of list
	std::list<int> another_list = { 2,4,5,6,7,8,9,10 };
	list.insert(list.end(), another_list.begin(), another_list.end());
	printContents(list);

	/* Deleting Elements */
	std::cout << "Deleting Elements...\n\n";
	
	// iterator points to newly added element -101
	auto iterator = list.insert(list.begin(), -101);
	printContents(list);

	list.erase(iterator);		// delete the element that iterator points to
	printContents(list);

	auto i = std::find(list.begin(), list.end(), 9);
	list.erase(i);
	printContents(list);

	// Delete all 4's
	while ((i = std::find(list.begin(), list.end(), 4)) != list.end())
		list.erase(i);
	printContents(list);

	list.erase(list.begin(), list.end());
	printContents(list);
	
	list.insert(list.begin(), 5, 7);
	printContents(list);
	
	std::cout << "There is " << list.size() << " elements...\n";

	list.clear();
	printContents(list);


}