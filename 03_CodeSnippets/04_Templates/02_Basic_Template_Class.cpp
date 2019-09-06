#include<iostream>

template<typename T>
class Storage {
public:
	Storage(T data): data_(data) {}

	void SetData(const T& data) {
		data_ = data;
	}

	T& GetValue() {
		return data_;
	}

private:
	T data_;
};


int main() {
	
	Storage<int> intStorage(5);
	std::cout << intStorage.GetValue() << '\n';

	Storage<std::string> strStorage( std::string("Hello World") );
	std::cout << strStorage.GetValue() << '\n';
	

}
