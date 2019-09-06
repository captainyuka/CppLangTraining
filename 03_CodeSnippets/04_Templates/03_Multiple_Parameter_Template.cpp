#include<iostream>

template<typename K, typename V>
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

private:
	K key_;
	V value_;
};


int main() {
	
	MapEntry<int, std::string> member_name(1, "Mustafa Katipoglu");
	std::cout << member_name.GetKey() << ":" << member_name.GetValue() << '\n';



}
