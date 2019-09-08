#include<iostream>	
#include<forward_list>

template<class T>
void printContents(const T& container);		// Generic print for containers

/* std::forward_list is a singly linked list—that is, it allows iteration in only one direction */

int main() {

	std::forward_list<int> singly_linked_list{ 1,3,2,7,-1, 9 };
	singly_linked_list.push_front(0);

	printContents(singly_linked_list);
	
	singly_linked_list.remove(3);
	printContents(singly_linked_list);

	singly_linked_list.sort();
	printContents(singly_linked_list);
	
	// As the forward_list doesn’t support bidirectional iteration, 
	// you can use operator++ on an iterator, but not operator-- .

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



