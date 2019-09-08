#include<iostream>		
#include<deque>

/*
 * deque is an STL dynamic array class quite similar in properties to that of the vector 
    except that it allows for the insertion and removal of elements at the front and back of the array.
*/

template<class T>	
void printDeque(std::deque<T>& t, std::string additional_note) {		
	std::cout << additional_note << ' ';
	for (auto i = 0; i < t.size(); ++i)
		std::cout << t.at(i) << ' ';
}

template <class T>
void printState(std::deque<T>& arr, std::string additional_note = "arr:") {
	printDeque(arr, additional_note);
	std::cout << "\tSize: " << arr.size() << "\n\n";
}

int main() {
	std::deque<int> deque = { 1,3,5,7 };
	printState(deque);

	deque.push_back(9);
	deque.push_back(11);
	printState(deque);

	deque.push_front(0);
	deque.push_front(-1);	
	printState(deque);

	deque.pop_back();
	deque.pop_back();
	deque.pop_back();
	printState(deque);

	deque.pop_front();
	deque.pop_front();
	deque.pop_front();
	printState(deque);

	deque.clear();
	printState(deque);

	deque = std::deque<int>(5);
	printState(deque);
	for (auto i = deque.begin(); i != deque.end(); ++i) {
		auto distance = std::distance(deque.begin(), i);
		*i = distance;
	}
	printState(deque);

	auto i = std::find(deque.begin(),deque.end(), 2);
	deque.erase(i);					// delete exact position
	printState(deque);

	deque.erase(deque.begin(),deque.end());		// clear all elements
	printState(deque);

	if (deque.empty())			// check is empty
		std::cout << "Deque is totally empty now...\n";

}