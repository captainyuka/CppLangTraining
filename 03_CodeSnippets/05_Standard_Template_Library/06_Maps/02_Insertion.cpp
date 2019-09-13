#include<iostream>	
#include<map>

template <class T>
void DisplayContents(const T& container) {
	for (auto i = container.begin(); i != container.end(); ++i)
		std::cout << i->first << " -> " << i->second << '\n';
	std::cout << '\n';
}

template <typename KeyType>
struct ReverseSort {
	bool operator() (const KeyType& key1, const KeyType& key2 ) const{
		return ( key1 > key2);
	}	
};

typedef std::map<int, std::string> MAP;

// Most functions in a map and multimap work in a similar fashion. 
// They accept similar parameters and return similar value types.
int main() {
	std::map<int, std::string> map;

	// insert a pair using make_pair func
	map.insert( std::make_pair(-1, "Minus One") );
	
	// insert a std::pair object directly
	map.insert( std::pair<int, std::string>(1000, "One Thousand") );

	// insert using value_type
	map.insert( MAP::value_type(3, "three") );

	// use subscript operator[]
	map[50] = "Fifty";			// key = 50, value = "fifty"

	std::cout << "The map contains " << map.size() << " key-value pairs.Thay are: \n";
	DisplayContents(map);
	
	// init a map that is copy of the map
	MAP copy_map(map.cbegin(), map.cend());


}
