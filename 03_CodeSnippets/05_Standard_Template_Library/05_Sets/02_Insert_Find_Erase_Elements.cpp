#include<iostream>	
#include<set>								// set and multiset classes


template<class T>
void printContents(const T& container);		// Generic print for containers

int main() {
	std::set<int> set{ 202, 151, -999, -1 };// init with C++11 initializer list
	
	// Inserting elements into set
	set.insert(-1);							// try to insert duplicate
	printContents(set);						// 202, 151, -999, -1

	// Inserting element into multiset
	std::multiset<int> multiset;
	multiset.insert(set.cbegin(), set.cend());
	multiset.insert(-1);					// try to insert duplicate
	printContents(multiset);				// -999, -1, -1, 151, 202
	
	// Counting number of an element
	std::cout << "Number of '-1's in multiset: " << multiset.count(-1) << '\n';

	// Finding an element
	std::multiset<int>::const_iterator element_found = multiset.find(202);
	// Check if found
	if (element_found != multiset.cend())
		std::cout << *element_found <<  " Found\n";
	else
		std::cout << "Not Found\n";

	// Erasing elements
	std::multiset<int> mset{ 13, 78, 78, -1, 124 };
	std::cout << "Multiset Contains " << mset.size() << " elements...\n";
	printContents(mset);

	std::cout << "Enter a number to erase from the set: ";
	int in = 0;
	std::cin >> in;

	std::cout << "Erasing " << mset.count(in) << " instances of the value " << in << '\n';
	mset.erase(in);								// delete all instances of the given value

	std::cout << "Multiset now contains " << mset.size() << " elements: ";
	printContents(mset);

	std::cout << "Enter a number to erase first instance of it from the set: ";
	in = 0;
	std::cin >> in;
	std::multiset<int>::iterator i = std::find(mset.begin(), mset.end(), in);
	if (i != mset.end())
		mset.erase(i);							// delete the element iterator points to
	else
		std::cout << "Element not found...\n";

	mset.erase(mset.begin(), mset.end());		
	mset.clear();								// delete all elements in the multiset


}

template<class T>
void printContents(const T& container) {	// Generic Print for containers
	if (container.empty()) {
		std::cout << "Container is totally empty...\n";
		return;
	}

	for (auto i = container.cbegin(); i != container.cend(); ++i)
		std::cout << *i << ' ';
	std::cout << "\n\n";
}



