#include<iostream>
#include<sstream>		// for std::ostringstream
#include<string>		// for c_str()

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	operator const char*() {
		std::ostringstream formattedDate;		// assist string construction
		formattedDate << day_ << " / " << month_ << " / " << year_;

		date_in_string_ = formattedDate.str();
		return date_in_string_.c_str();
	}

private:
	int day_, month_, year_;
	std::string date_in_string_;
};

int main() {
	Date date(4, 9, 2019);
	std::cout << "Today's date is: " << date << '\n';

	std::string todays_date(date);
	std::cout << "todays_date: " << todays_date << '\n';
}

