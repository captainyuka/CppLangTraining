#include<iostream>
#include<algorithm>
#include<string>

void print(std::string str) {
	std::cout << str << '\n';
}

int main() {
	std::string str("This is a loong string that contains lots of characters which is totally waste of bytes.P");
	print(str);

	// Delete characters given position and count
	str.erase(3,57);										// # erase(position,count)
	print(str);

	// find character 'b' using find algorithm
	std::string::iterator i = find(str.begin(), str.end(), 'b');

	if (i != str.end())
		str.erase(i);			// delete character b		// # erase(position)
	print(str);
	
	// Delete a range of characters
	str.erase(str.begin(), str.end());						// # erase(start_position, end_position)

	if (str.length() == 0)
		std::cout << "String is totally empty...\n";

	std::string new_str("This new string will be cleared...");
	print(new_str);

	new_str.clear();										// clears the internal buffer and resets the string object.
	print(new_str);

	if (new_str.length() == 0)
		std::cout << "new_str is totally empty...\n";

}