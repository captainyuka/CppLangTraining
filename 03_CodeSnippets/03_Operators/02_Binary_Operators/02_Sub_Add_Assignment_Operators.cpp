#include<iostream>

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	void DisplayDate() {
		std::cout << day_ << " / " << month_ << " / " << year_ << '\n';
	}
	
	void operator+= (int days_to_add) {		//addition assignment operator
		day_ += days_to_add;
	}

	void operator-= (int days_to_sub) {		// subtraction assignment operator
		day_ -= days_to_sub;
	}

	void operator-= (Date& days_to_add) {	// Overloaded subtraction assigment
		day_ -= days_to_add.GetDay();
	}

	int GetDay() {
		return day_;
	}

private:
	int day_, month_, year_;
};

int main() {
	Date date(15, 3, 1908);
	std::cout << "Date: \n";
	date.DisplayDate();
	
	std::cout << "Before the date: ";
	date -= 14;
	date.DisplayDate();

	std::cout << "Actual Date: ";
	date += 30;
	date.DisplayDate();

	std::cout << "Kind of funny implementation but you get the point: ";
	Date otherDate(14, 05, 2015);
	date -= otherDate;
	date.DisplayDate();
}

