#include<iostream>	
#include<string>
#include<set>

template <class T>
void DisplayContents(const T& container) {
	for (auto i = container.begin(); i != container.end(); ++i)
		std::cout << *i << '\n';
	std::cout << '\n';
}

class ContactItem {
public:
	
	ContactItem(const std::string& name, const std::string& phone) {
		name_ = name;
		phone_num_ = phone;
		display_as_ = (name + ": " + phone);
	}

	// used by std::find() given contact list item
	bool operator == (const ContactItem& other) const{
		return  this->name_ == other.GetName();
	}
	
	// used to sort
	bool operator < (const ContactItem& other) const{
		return this->name_ < other.GetName();
	}
	
	// Used in DisplayContents via std::cout
	operator const char* () const{
		return display_as_.c_str();
	}

	std::string GetDisplayAs() const {
		return display_as_;
	}

	std::string GetPhoneNum() const {
		return phone_num_;
	}

	std::string GetName() const{
		return name_;
	}
private:
	std::string name_;
	std::string phone_num_;
	std::string display_as_;
};

int main() {
	std::set<ContactItem> contacts;
	contacts.insert(ContactItem("Jack Welsch", "+1 7889 879 879"));
	contacts.insert(ContactItem("Bill Gates", "+1 97 7897 8799 8"));
	contacts.insert(ContactItem("Angi Merkel", "+49 23456 5466"));
	contacts.insert(ContactItem("Vlad Putin", "+7 6645 4564 797"));
	contacts.insert(ContactItem("John Travolta", "91 234 4564 789"));
	contacts.insert(ContactItem("Ben Affleck", "+1 745 641 314"));

	std::cout << "Enter a name you wish to delete: ";
	std::string input_name;
	std::getline(std::cin, input_name);

	auto contact_found = contacts.find(ContactItem(input_name, ""));
	if (contact_found != contacts.end()) {
		contacts.erase(contact_found);
		std::cout << "Displaying contents after erasing " << input_name << '\n';
		DisplayContents(contacts);
	}
	else
		std::cout << "Contact not found...\n";

}
