#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <cstring>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Использование: ./read-file <путь_к_файлу>" << std::endl;
		return 1;
	}
	const char* filePath = argv[1];
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Ошибка при открытии файла: " << std::strerror(errno) << std::endl;
		return 1;
	}
	const size_t bufferSize = 1024;
	char buffer[bufferSize];
	while (file.read(buffer, bufferSize)) {
		std::cout.write(buffer, file.gcount());
	}
	if (file.gcount() > 0) {
		std::cout.write(buffer, file.gcount());
	}
	file.close();
	return 0;
}
