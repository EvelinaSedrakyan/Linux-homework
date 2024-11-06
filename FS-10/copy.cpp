#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>

void copyFile(const char* srcPath, const char* dstPath) {
	int srcFd = open(srcPath, O_RDONLY);
	if (srcFd == -1) {
		std::cerr << "Ошибка при открытии исходного файла: " << strerror(errno) << std::endl;
		exit(1);
	}
	int dstFd = open(dstPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dstFd == -1) {
		std::cerr << "Ошибка при открытии целевого файла: " << strerror(errno) << std::endl;
		close(srcFd);
		exit(1);
	}
	struct stat srcStat;
	if (fstat(srcFd, &srcStat) == -1) {
		std::cerr << "Ошибка при получении информации о файле: " << strerror(errno) << std::endl;
		close(srcFd);
		close(dstFd);
		exit(1);
	}
	off_t totalCopied = 0;
	off_t totalHoles = 0;  
	const size_t bufferSize = 4096;
	char buffer[bufferSize];
	while (true) {
		ssize_t bytesRead = read(srcFd, buffer, bufferSize);
		if (bytesRead == -1) {
			std::cerr << "Ошибка при чтении из исходного файла: " << strerror(errno) << std::endl;
			close(srcFd);
			close(dstFd);
			exit(1);
		}
		if (bytesRead == 0) {
			break;
		}
		ssize_t bytesWritten = write(dstFd, buffer, bytesRead);
		if (bytesWritten == -1) {
			std::cerr << "Ошибка при записи в целевой файл: " << strerror(errno) << std::endl;
			close(srcFd);
			close(dstFd);
			exit(1);
		}
		totalCopied += bytesWritten;
		if (bytesWritten < bytesRead) {
			totalHoles += (bytesRead - bytesWritten); 
		}
	}
	struct stat dstStat;
	if (fstat(dstFd, &dstStat) == -1) {
		std::cerr << "Ошибка при получении информации о целевом файле: " << strerror(errno) << std::endl;
		close(srcFd);
		close(dstFd);
		exit(1);
	}
	std::cout << "Successfully copied " << srcStat.st_size << " bytes (data: " << totalCopied << ", hole: " << totalHoles << ")." << std::endl;
	close(srcFd);
	close(dstFd);
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Использование: ./copy <путь к исходному файлу> <путь к целевому файлу>" << std::endl;
		return 1;
	}
	const char* srcPath = argv[1];
	const char* dstPath = argv[2];
	copyFile(srcPath, dstPath);
	return 0;
}
