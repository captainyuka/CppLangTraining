#include<iostream>	
#include<map>

template <class T>
void DisplayContents(const T& container) {
	for (auto i = container.begin(); i != container.end(); ++i)
		std::cout << *i << '\n';
	std::cout << '\n';
}

template <typename KeyType>
struct ReverseSort {
	bool operator() (const KeyType& key1, const KeyType& key2 ) const{
		return ( key1 > key2);
	}	
};

// To facilitate quick searching, STL implementations of the map and multimap 
// internally look like binary trees.

int main() {
	// Note that the default sort (in the previous instantiations) uses std::less<T>
	// that would sort elements in the increasing order.
	std::map<int, std::string> int_to_string_map;
	std::multimap<int, std::string> int_to_string_multimap;
	
	// init map with default sort predicate
	std::map<int, std::string, std::less<int>> map;				// third parameter is optional
	std::multimap<int, std::string, std::less<int>> multimap;	// default is std::less<>

	// init map with user defined predicate
	std::map<int, std::string, ReverseSort<int>> map1();		// supply class or struct that implements operator()
	std::multimap<int, std::string, ReverseSort<int>> multimap1();

	// init map as a copy of another
	std::map<int, std::string> map2(map.cbegin(), map.cend());
	std::multimap<int, std::string> multimap2(map.cbegin(), map.cend());

	// init map with a predicate that inverses sort order using elements of another
	std::map<int, std::string, ReverseSort<int>> map3(map2.cbegin(), map2.cend());
	std::multimap<int, std::string, ReverseSort<int>> multimap3(map.cbegin(), map.cend());
}
