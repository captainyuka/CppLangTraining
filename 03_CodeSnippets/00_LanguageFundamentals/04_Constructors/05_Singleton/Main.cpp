#include<iostream>

class President {

private:
	President() {}// private default constructor			
	President(const President&);					// private copy constructor
	const President& operator=(const President&);	// private assignment operator

	std::string name;

public:
	static President& GetInstance() {
		static President singleton;
		return singleton;
	}

	std::string GetName() {
		return name;
	}

	void SetName(std::string name) {
		this->name = name;
	}

};


int main() {
	President& p = President::GetInstance();
	p.SetName("Mustafa");
	std::cout << p.GetName() << '\n';

	// variable x is alias for variable p
	President& x = President::GetInstance();
	std::cout << x.GetName();

//	President president;							// can not access constructor
//	President* president = new President();			// can not access constructor
//	President president = p;						// can not access copy constructor
//	President president = President::GetInstance(); // can not access assignment operator
} 

