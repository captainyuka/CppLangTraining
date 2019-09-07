#include<iostream>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	std::string str = "look for a needle in a haystack," 
					"here come some unnecessary hay words"
					"since we will be searching all instances of hay keyword"
					"in this sentence anyway lets say one more hay";

	// Use the utility std::string::find()
	auto char_pos = str.find("hay", 0);			// Find "hay" start index 0 for search

	// Check if found
	if (char_pos == std::string::npos) {
		std::cout << "Substring not found\n";
		return 0;			// no need to continue
	}

	std::cout << "First instance of \"day\" was found at position " << char_pos << '\n';
	std::cout << "\nLocating all instances of \"day\" in the sentence\n";

	int search_offset = 0;

	int sub_str_pos;
	while ((sub_str_pos = str.find("hay", search_offset)) != std::string::npos) {
		std::cout << "\"hay\" found at position " << sub_str_pos << '\n';
		search_offset = sub_str_pos + 1;
	}
}