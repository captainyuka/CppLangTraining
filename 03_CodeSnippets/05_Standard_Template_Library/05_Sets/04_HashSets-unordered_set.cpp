#include<iostream>	
#include<unordered_set>

template <class T>
void DisplayContents(const T& container) {
	for (auto i = container.begin(); i != container.end(); ++i)
		std::cout << *i << '\n';
	std::cout << '\n';

	std::cout << "Number of elements, size() = " << container.size() << '\n';
	std::cout << "Bucket count = " << container.bucket_count() << '\n';
	std::cout << "Max load factor = " << container.max_load_factor() << '\n';
	std::cout << "Load factor: " << container.load_factor() << "\n\n";
}

int main() {
	std::unordered_set<int> hashset;
	std::unordered_multiset<int> multi_hashset;

	// insert
	hashset.insert(1000);
	multi_hashset.insert(5);

	// find
	auto element_found = hashset.find(1000);
	if (element_found != hashset.end())
		std::cout << *element_found << '\n';

	// Hash function
	std::unordered_set<int>::hasher hash_func = hashset.hash_function();
	std::cout << "\n\n";

	std::unordered_set<int> hashset1{ 1, -3, 2017, 300, -1, 989, -300, 9 };
	DisplayContents(hashset1);
	hashset1.insert(999);
	DisplayContents(hashset1);

	std::cout << "Enter in you want to check for existence in set: ";
	int in = 0;
	std::cin >> in;
	auto element_found1 = hashset1.find(in);
	if (element_found1 != hashset1.end())
		std::cout << *element_found1 << " found in set\n";
	else
		std::cout << in << "not found in the set\n";
}
