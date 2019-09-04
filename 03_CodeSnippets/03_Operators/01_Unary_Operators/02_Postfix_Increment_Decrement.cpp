#include<iostream>

class Date {
public:
	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {};

	Date& operator ++(){		// prefix increment operator
		++day_;
		return *this;
	}

	Date& operator --() {		// prefix decrement operator
		--day_;
		return *this;
	}

	Date operator ++(int) {		// postfix increment operator
		Date copy(day_, month_, year_);
		++day_;
		return copy;
	}

	Date operator --(int) {		// postfix decrement operator
		Date copy(day_, month_, year_);
		--day_;
		return copy;
	}

	void DisplayDate() {
		std::cout << day_ << " / " << month_ << " / " << year_;
	}

private:
	int day_, month_, year_;
};

int main() {
	Date holiday(1, 1, 2020);
	holiday.DisplayDate();
	std::cout << '\n';

	++holiday;
	holiday.DisplayDate();
	std::cout << '\n';
	
	--holiday;
	holiday.DisplayDate();
	std::cout << '\n';
	
	holiday++;
	holiday.DisplayDate();
	std::cout << '\n';
	
	holiday--;
	holiday.DisplayDate();
	std::cout << '\n';
	

}

