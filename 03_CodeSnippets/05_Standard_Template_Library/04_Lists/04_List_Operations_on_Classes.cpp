#include<iostream>	
#include<string>
#include<list>

template<class T>
void printContents(const T& container);		// Generic print for containers

struct ContactItem {
	std::string name_;
	std::string phone_;
	std::string display_as_;
	
	ContactItem(const std::string& name, const std::string& phone) {
		name_ = name;
		phone_ = phone;
		display_as_ = (name + ": " + phone);
	}

	bool operator == (const ContactItem& other) const{
		return (other.name_ == name_);
	}

	bool operator < (const ContactItem& other) const{
		return (name_ < other.name_);
	}

	operator const char* () const{
		return display_as_.c_str();
	}
};

bool SortOnPhoneNumber(const ContactItem& x, const ContactItem& y) {
	return x.phone_ < y.phone_;
}

int main() {
	std::list<ContactItem> contacts;
	contacts.push_back( ContactItem("Vlad Putin", "+7 66454564797"));
	contacts.push_back( ContactItem("Angi Merkel", "+49 234565466"));
	contacts.push_back( ContactItem("Artie J. Baldwin", "+2 107672813"));
	contacts.push_back( ContactItem("Denise S. Garner", "+25 231476566"));

	printContents(contacts);								// Uses const char* conversion operator

	std::cout << "Sorting in alphabetical order via operator<\n";
	contacts.sort();										// uses less than operator
	printContents(contacts);

	std::cout << "Sorting in order of phone numbers via predicate:\n";
	contacts.sort(SortOnPhoneNumber);						
	printContents(contacts);
	
	std::cout << "Erasing Merkel from the list: \n";
	contacts.remove(ContactItem("Angi Merkel",""));			// uses equality operator
	printContents(contacts);

}


template<class T>
void printContents(const T& container) {	// Generic Print for containers
	if (container.empty()) {
		std::cout << "Container is totally empty...\n";
		return;
	}

	for (auto i = container.cbegin(); i != container.cend(); ++i)
		std::cout << *i << '\n';
	std::cout << "\n\n";
}

