#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void execute_command(const string& input) {
	string command = input;
	bool silent = false;
	if (command.substr(0, 7) == "silent ") {
		silent = true;
		command = command.substr(7);
	}
	vector<char*> args;
	stringstream ss(command);
	string word;
	while (ss >> word) {
		args.push_back(strdup(word.c_str()));
	}
	args.push_back(nullptr);
	setenv("PATH", (string(getenv("PATH")) + ":.").c_str(), 1);
	if (silent) {
		pid_t pid = fork();
		if (pid == 0) {
			string log_file = to_string(getpid()) + ".log";
			freopen(log_file.c_str(), "w", stdout);
			freopen(log_file.c_str(), "w", stderr);
			execvp(args[0], args.data());
			cerr << "Exec failed: " << strerror(errno) << endl;
			exit(1);
		} else if (pid > 0) {
			waitpid(pid, nullptr, 0);
		} else {
			cerr << "Fork failed: " << strerror(errno) << endl;
		}
	} else {
		pid_t pid = fork();
		if (pid == 0) {
			execvp(args[0], args.data());
			cerr << "Exec failed: " << strerror(errno) << endl;
			exit(1);
		} else if (pid > 0) {
			waitpid(pid, nullptr, 0);
		} else {
			cerr << "Fork failed: " << strerror(errno) << endl;
		}
	}
}

int main() {
	string input;
	while (true) {
		cout << "shell> ";
		getline(cin, input);
		if (input == "exit") {
			break;
		}
	execute_command(input);
	}
	return 0;
}
