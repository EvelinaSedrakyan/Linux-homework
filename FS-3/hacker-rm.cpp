#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <cerrno>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Использование: ./hacker-rm <путь к файлу>" << std::endl;
		return 1;
	}
	const char* filePath = argv[1];
	struct stat fileStat;
	if (stat(filePath, &fileStat) != 0) {
		std::cerr << "Ошибка при проверке файла: " << std::strerror(errno) << std::endl;
		return 1;
	}
	int fd = open(filePath, O_WRONLY);
	if (fd == -1) {
		std::cerr << "Ошибка при открытии файла для записи: " << std::strerror(errno) << std::endl;
		return 1;
	}
	if (lseek(fd, 0, SEEK_END) == -1) {
		std::cerr << "Ошибка при перемещении указателя в конец файла: " << std::strerror(errno) << std::endl;
		close(fd);
		return 1;
	}
	off_t fileSize = fileStat.st_size;
	char nullByte = '\0';
	for (off_t i = 0; i < fileSize; ++i) {
		if (write(fd, &nullByte, 1) != 1) {
			std::cerr << "Ошибка при записи нулевых байтов в файл: " << std::strerror(errno) << std::endl;
			close(fd);
			return 1;
		}
	}
	close(fd);
	if (unlink(filePath) != 0) {
		std::cerr << "Ошибка при удалении файла: " << std::strerror(errno) << std::endl;
		return 1;
	}
	std::cout << "Файл " << filePath << " успешно удален." << std::endl;
	return 0;
}
