#include<iostream>

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	void DisplayDate() {
		std::cout << day_ << " / " << month_ << " / " << year_ << '\n';
	}

	bool operator < (const Date& compareTo) {
		if (year_ < compareTo.GetYear())
			return true;
		else if (year_ > compareTo.GetYear())
			return false;
		else if (month_ < compareTo.GetMonth())
			return true;
		else if (month_ > compareTo.GetMonth())
			return false;
		else if (day_ < compareTo.GetDay())
			return true;
		else
			return false;
	}

	bool operator <= (const Date& compareTo) {
		if (this->operator==(compareTo))
			return true;
		return this->operator<(compareTo);
	}

	bool operator > (const Date& compareTo) {
		return !(this->operator<=(compareTo));
	}

	bool operator >= (const Date& compareTo) {
		return (this->operator>(compareTo)) || (this->operator==(compareTo));
	}
	
	bool operator== (const Date& compareTo) {
		return (	 (day_ == compareTo.GetDay()) 
				  && ( month_ == compareTo.GetMonth()) 
				  && ( year_ == compareTo.GetYear()) 
			   );
	}

	bool operator!= (const Date& compareTo) {
		return !(this->operator==(compareTo));
	}

	int GetDay() const { return day_; }
	int GetMonth() const { return month_; }
	int GetYear() const { return year_; }

private:
	int day_, month_, year_;
};

int main() {

	Date first(31,3,1908);
	Date second(31,3,1908);

	if (first == second)
		std::cout << "Both dates are equal to each other...\n";
	else
		std::cout << "Dates are not equal to each other...\n";

	Date x(30,3,1908);

	if (x < first)
		std::cout << "x less than first\n";
	
	Date y(30, 4, 1908);
	if (y <= first)
		std::cout << "y less then or equal to first\n";
	else
		std::cout << "y is not less then or equal to first\n";

	if (x >= y)
		std::cout << "x greater then or equal to y\n";
	else
		std::cout << "x is not greater then or equal to y\n";

	

}


