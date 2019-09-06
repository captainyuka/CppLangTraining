#include<iostream>

class DynIntegers {
public:
	DynIntegers(int size) {
		data_ = new int[size];
		size_ = size;
	}
	
	DynIntegers(int size, int init) {
		data_ = new int[size];
		size_ = size;
		for (auto i = 0; i < size; ++i)
			data_[i] = init;
	}
	
	DynIntegers(const DynIntegers& copy_src);				// Copy Constructor
	DynIntegers& operator= (const DynIntegers& copy_src);	// Copy Assignment Operator
	
	DynIntegers(DynIntegers&& move_src);					// Move Constructor
	DynIntegers& operator= (DynIntegers&& move_src);		// Move Assignment Operator

	DynIntegers operator+ (const DynIntegers& src);

	int& operator[] (int index);
	const int& operator[] (int index) const;

	void print() {
		for (auto i = 0; i < size_; ++i)
			std::cout << i << " : "<< data_[i] << '\n';
	}

	~DynIntegers() {
		std::cout << "Destructor Called...\n";
		delete[] data_;
	}

	int* GetData() const{
		return data_;
	}

	void SetData(int* data) {
		data_ = data;
	}

	auto GetSize() const {
		return size_;
	}

	void SetSize(int size) {
		size_ = size;
	}

private:
	int* data_;
	int size_;

	void InvalidInit() {
		size_ = -1;
		data_ = nullptr;
	}
};

DynIntegers& DynIntegers::operator= (DynIntegers&& move_src){
	std::cout << "Move Assignment Operator...\n";
	if (move_src.GetData() == nullptr || this == &move_src)
		return *this;

	if (data_ != nullptr)
		delete[] data_;

	data_ = move_src.GetData();
	move_src.SetData(nullptr);

	size_ = move_src.GetSize();
	move_src.SetSize(-1);

	return *this;
}

DynIntegers::DynIntegers(DynIntegers&& move_src) {
	std::cout << "Move Constructor...\n";
	if (move_src.GetData() == nullptr) {
		InvalidInit();
		return;
	}
	
	data_ = move_src.GetData();
	move_src.SetData(nullptr);			
	
	size_ = move_src.GetSize();
	move_src.SetSize(-1);	
}

DynIntegers::DynIntegers(const DynIntegers& copy_src){
	std::cout << "Copy Constructor...\n";
	if (copy_src.GetData() == nullptr) {
		InvalidInit();
		return;
	}

	const int* data = copy_src.GetData();
	
	size_ = copy_src.GetSize();
	data_ = new int[ size_ ];
	
	for (auto i = 0; i < size_; i++)
		data_[i] = data[i];
}
const int& DynIntegers::operator[](int index) const{
	static int* error = new int;
	*error = INT_MIN;
	if (data_ == nullptr || index <= 0 || index >= size_)
		return *error;

	return data_[index];
}

int& DynIntegers::operator[](int index){
	static int* error = new int;
	*error = INT_MIN;
	if (data_ == nullptr || index <= 0 || index >= size_)
		return *error;

	return data_[index];
}

DynIntegers& DynIntegers::operator=(const DynIntegers& copy_src){		// Copy Assignment Operator
	std::cout << "Copy Assignment Operator...\n";
	const int* data = copy_src.GetData();
	const int size = copy_src.GetSize();

	if (data == nullptr || this == &copy_src)
		return *this;
	
	if (data_ != nullptr)
		delete[] data_;
	
	// Ensure deep copy
	data_ = new int[size];
	size_ = size;
	for (auto i = 0; i < size; ++i)
		data_[i] = data[i];

	return *this;
}

DynIntegers DynIntegers::operator+ (const DynIntegers& src) {
	std::cout << "+ operator...\n";
	int temp_size = GetSize() + src.GetSize();
	DynIntegers temp(temp_size);

	int* temp_data = temp.GetData();
	const int* data = src.GetData();
	const int size = src.GetSize();

	int i;
	for (i = 0; i < size_; ++i)
		temp_data[i] = data_[i];
	for (int j = 0; j < size; ++i, ++j)
		temp_data[i] = data[j];

	return temp;
}

void doSomething(DynIntegers x) {
	x.print();
}

int main() {
	DynIntegers arr(5,0);
	arr.print();

	DynIntegers arr2(5,3);
	arr2.print();

	doSomething(DynIntegers(5, 2) + DynIntegers(3, 2) + DynIntegers(5,3));
}
