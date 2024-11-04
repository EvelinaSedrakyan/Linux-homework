#include "Sort.h"
#include <algorithm>

void sortComplexNumbers(std::vector<Complex>& numbers) {
	std::sort(numbers.begin(), numbers.end(), [](const Complex& a, const Complex& b) {return a.abs() < b.abs();});
}
