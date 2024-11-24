#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <chrono>
void do_command(char** argv) {
	auto start = std::chrono::high_resolution_clock::now();
	pid_t pid = fork();
	if (pid == -1) {
		std::cerr << "Ошибка: не удалось создать процесс!" << std::endl;
		exit(1);
	}
	if (pid == 0) {
		if (execvp(argv[0], argv) == -1) {
			std::cerr << "Ошибка при выполнении команды: " << argv[0] << std::endl;
			exit(1);
		}
	} else {
		int status;
		waitpid(pid, &status, 0);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		if (WIFEXITED(status)) {
			std::cout << "Команда завершена с кодом " << WEXITSTATUS(status) << " и заняла " << duration.count() << " секунд." << std::endl;
		} else {
			std::cerr << "Команда не завершилась нормально." << std::endl;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Использование: ./do-command <команда> [аргументы...]" << std::endl;
		return 1;
	}
	std::vector<char*> args(argv + 1, argv + argc);
	args.push_back(nullptr);  
	char** command_args = args.data();
	do_command(command_args);
	return 0;
}
