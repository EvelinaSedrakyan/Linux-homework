#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <cstring>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Использование: ./simple-copy <исходный файл> <файл назначения>" << std::endl;
		return 1;
	}

	const char* sourceFile = argv[1];
	const char* destFile = argv[2];
	std::ifstream source(sourceFile, std::ios::binary);
	if (!source) {
		std::cerr << "Ошибка при открытии исходного файла: " << std::strerror(errno) << std::endl;
		return 1;
	}
	std::ofstream dest(destFile, std::ios::binary);
	if (!dest) {
		std::cerr << "Ошибка при открытии файла назначения: " << std::strerror(errno) << std::endl;
		return 1;
	}
	const size_t bufferSize = 1024;
	char buffer[bufferSize];
	while (source.read(buffer, bufferSize)) {
		dest.write(buffer, source.gcount());
	}
	if (source.gcount() > 0) {
		dest.write(buffer, source.gcount());
	}

	std::cout << "Копирование завершено успешно." << std::endl;

	source.close();
	dest.close();

	return 0;
}

