#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

void initialize(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Использование: ./redirect-cin <путь к файлу>" << std::endl;
		exit(1);
	}

	const char* filePath = argv[1];
	int fileDescriptor = open(filePath, O_RDONLY);
	if (fileDescriptor == -1) {
		std::cerr << "Ошибка при открытии файла: " << std::strerror(errno) << std::endl;
		exit(1);
	}
	if (dup2(fileDescriptor, STDIN_FILENO) == -1) {
		std::cerr << "Ошибка при перенаправлении ввода: " << std::strerror(errno) << std::endl;
		close(fileDescriptor);
		exit(1);
	}
	close(fileDescriptor);
}

int main(int argc, char** argv) {
	initialize(argc, argv);
	std::string input;
	std::cin >> input;
	std::string reversed(input.rbegin(), input.rend());
	std::cout << reversed << std::endl;

	return 0;
}
