#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

void writeToFile(int fd, const std::string& data) {
	if (write(fd, data.c_str(), data.size()) == -1) {
		std::cerr << "Ошибка при записи в файл: " << std::strerror(errno) << std::endl;
		exit(1);
	}
	if (write(fd, "\n", 1) == -1) {
		std::cerr << "Ошибка при записи символа новой строки в файл: " << std::strerror(errno) << std::endl;
		exit(1);
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Использование: ./manual-append <путь к файлу>" << std::endl;
		return 1;
	}

	const char* filePath = argv[1];
	int fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		std::cerr << "Ошибка при открытии файла: " << std::strerror(errno) << std::endl;
		return 1;
	}
	int fd1 = dup(fd);
	if (fd1 == -1) {
 		std::cerr << "Ошибка при дублировании дескриптора: " << std::strerror(errno) << std::endl;
		close(fd);
		return 1;
	}

	int fd2 = dup(fd);
	if (fd2 == -1) {
		std::cerr << "Ошибка при дублировании дескриптора: " << std::strerror(errno) << std::endl;
		close(fd);
		close(fd1);
		return 1;
	}
	writeToFile(fd1, "first line");
	writeToFile(fd2, "second line");
	close(fd);
	close(fd1);
	close(fd2);
	std::cout << "Запись в файл завершена успешно!" << std::endl;
	return 0;
}
