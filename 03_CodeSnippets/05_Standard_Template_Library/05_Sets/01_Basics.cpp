#include<iostream>	
#include<set>								// set and multiset classes


template<class T>
void printContents(const T& container);		// Generic print for containers


template<class T>
class SortDescending {
public:
	bool operator() (const T& x, const T& y) const {
		return (x > y);
	}
};


int main() {
	std::set<int> set;
	std::multiset<int> multiset;

	std::set<int>::iterator set_iterator;
	std::multiset<int>::iterator multiset_iterator;
	
	// set and multiset instantiated given a user-defined sort predicate
	std::set<int, SortDescending<int>> set1;				// SortDescending overloads operator ()
	std::multiset<int, SortDescending<int>> multiset1;
	
	// Creating one set from another
	std::set<int> set2(set);
	std::multiset<int> multiset3(set.cbegin(), set.cend());
}


/*
	To facilitate quick searching, STL implementations of the set and multiset internally
	look like a binary tree. This means that elements inserted in a set or a multiset are
	sorted on insertion for quicker lookups.
	
	These clasess use a default predicate std::less when you don’t supply a sort criteria. 
	This ensures that your set contains elements sorted in ascending order.

	You create a binary sort predicate by defining a class with operator()
	bool operator()(const T& lhs, const T& rhs) const{...}

	You then supply this predicate in the set or multiset instantiation as follows:
	// a set and multiset of integers (using sort predicate)
	set <int, SortDescending<int>> setInts;
	multiset <int, SortDescending<int>> msetInts;

*/


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



