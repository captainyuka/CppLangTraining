#include<iostream>	
#include<algorithm>
#include<list>

template<class T>
void printContents(const T& container, std::string note);		// Generic print for containers

/*
 *	Even though the STL supplies sort and reverse as algorithms that will and do work
	on the list class. The member versions of these algorithms ensure that iterators pointing 
	to elements in the list are not invalidated when the relative position of an element is disturbed.
*/

/*
 * binary predicate that helps the list’s sort() function decide whether one element is
less than the other. If not, it swaps their positions.
*/
bool MySortDescendingPredicate(const int& x, const int&y) {
	// Return true for desired order
	return x > y;
}

int main() {
	
	std::list<int> list{1,-1,2,-2,3,-3,4,-4,5,-5};	
	printContents(list, "Original List");

	// Reversal
	list.reverse();
	printContents(list, "After Reversal");

	// Sort in ascending order
	list.sort();
	printContents(list, "After Ascending Sort");
	
	// Sort in descending order or any order according to predicate
	list.sort(MySortDescendingPredicate);
	printContents(list, "After Descending Sort");

}


template<class T>
void printContents(const T& container, std::string note = "") {	// Generic Print for containers
	std::cout << note << "\n";

	if (container.empty()) {
		std::cout << "Container is totally empty...\n";
		return;
	}

	for (auto i = container.cbegin(); i != container.cend(); ++i)
		std::cout << *i << ' ';
	std::cout << "\n\n";
}

