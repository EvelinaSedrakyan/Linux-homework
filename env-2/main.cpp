#include <iostream>
#include <vector>
#include "Complex.h"
#include "Sort.h"

int main() {
	std::vector<Complex> numbers = {Complex(3.0, 4.0), Complex(1.0, 1.0), Complex(0.0, 2.0), Complex(2.0, -3.0)};
	std::cout << "Массив до сортировки:\n";
	for (const auto& num : numbers) {
		num.print();
		std::cout << "\n";
	}

	sortComplexNumbers(numbers);
	std::cout << "Массив после сортировки:\n";
	for (const auto& num : numbers) {
		num.print();
		std::cout << "\n";
	}
	 return 0;
}
