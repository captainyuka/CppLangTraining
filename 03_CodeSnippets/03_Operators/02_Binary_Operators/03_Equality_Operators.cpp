#include<iostream>

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};
	
	void DisplayDate() {
		std::cout << day_ << " / " << month_ << " / " << year_ << '\n';
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
}


