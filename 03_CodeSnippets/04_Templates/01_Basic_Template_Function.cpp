#include<iostream>

template<typename T>
const T& GetMax(const T& first, const T& second) {
	if (first > second)
		return first;
	else
		return second;
}

int main() {
	int result = GetMax<int>(8,7);				// Compiler Generates int version of the function
	std::cout << result << '\n';
	std::cout << GetMax(5,3) << '\n';

	double res = GetMax<double>(5.3,2.6);		// Compiler Generates double version of the function
	std::cout << res << '\n';

	
/*
 * Note the detail <int> used in the call to GetMax . 
	It effectively defines the template parameter objType as int. 
	The preceding code leads to the compiler generating	two versions of the template function GetMax
 */

}
