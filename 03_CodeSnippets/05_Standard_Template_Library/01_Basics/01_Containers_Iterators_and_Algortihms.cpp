#include<iostream>
#include<vector>
#include<algorithm>


int main() {

	{
		using namespace std;

		vector<int> int_arr;				// container
		int_arr.push_back(58);
		int_arr.push_back(2992);
		int_arr.push_back(25);
		int_arr.push_back(9988);

		cout << "The Contents of the Vector: \n";

		vector<int>::iterator arr_iterator = int_arr.begin();		// iterator
		while(arr_iterator != int_arr.end()) {						// end points to after the last element
			cout << *arr_iterator << '\n';
			++arr_iterator;
		}

		// Find an element using 'find' algorithm

		vector<int>::iterator el_found = find(int_arr.begin(), int_arr.end(), 25);		
		if (el_found != int_arr.end()) {
			// determine the position of element using std::distance
			int position = distance(int_arr.begin(), el_found);
			cout << *el_found << " found in the vector at position " << position << '\n';
		}
	
	}

}
