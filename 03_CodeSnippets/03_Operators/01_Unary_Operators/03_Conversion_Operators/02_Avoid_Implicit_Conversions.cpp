#include<iostream>
#include<sstream>		// for std::ostringstream
#include<string>		// for c_str()

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	explicit operator const char*() {	// To avoid implicit conversions use explicit keyword
		std::ostringstream formattedDate;		
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
	// Using explicit would force the programmer to assert his intention to convert using a cast: 
	std::cout << "Today's date is: " << static_cast<const char*>(date) << '\n';

	std::string todays_date(static_cast<const char*>(date));
	std::cout << "todays_date: " << todays_date << '\n';
}

