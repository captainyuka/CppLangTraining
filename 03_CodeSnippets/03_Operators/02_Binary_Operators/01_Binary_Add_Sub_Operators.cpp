#include<iostream>

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	void DisplayDate() {
		std::cout << day_ << " / " << month_ << " / " << year_ << '\n';
	}
	
	Date operator + (int days_to_add) {		// binary addition operator
		return Date(day_ + days_to_add, month_, year_);
	}

	Date operator - (int days_to_sub) {		// binary subtraction operator
		return Date(day_ - days_to_sub, month_, year_);
	}
private:
	int day_, month_, year_;
};

int main() {
	Date date(15, 3, 1908);
	std::cout << "Date: \n";
	date.DisplayDate();
	
	Date before_the_date( date - 14);
	std::cout << "Before the date: ";
	before_the_date.DisplayDate();

	Date actual_date(date + 16);
	std::cout << "Actual Date: ";
	actual_date.DisplayDate();
}

