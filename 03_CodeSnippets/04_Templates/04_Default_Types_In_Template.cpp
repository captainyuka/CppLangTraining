#include<iostream>

template<typename K = int, typename V = std::string>
class MapEntry {
public:	
	MapEntry(K key, V value) : key_(key), value_(value){}

	void SetKey(K key) {
		key_ = key;
	}

	void SetValue(V value) {
		value_ = value;
	}

	K& GetKey() {
		return key_;
	}

	V& GetValue() {
		return value_;
	}

	void Print() {
		std::cout << key_ << " : " << value_ << '\n';
	}

private:
	K key_;
	V value_;
};


int main() {
	
	MapEntry<int, std::string> member_name(1, "Mustafa Katipoglu");
	member_name.Print();

	MapEntry<> member_name2(2, "Yusuf Sertan Gunes");		// Declare with default types
	member_name2.Print();
}
