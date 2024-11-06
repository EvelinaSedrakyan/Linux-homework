#include <iostream>
#include "fileutils.h"
#include <string>

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Usage: ./program <source_file> <destination_file>" << std::endl;
		return 1;
	}
	std::string source = argv[1];
	std::string dest = argv[2];
	log_action("Started copying " + source);
	if (copy_file(source, dest)) {
		std::cout << "File copied successfully!" << std::endl;
		log_action("Copy completed");
	} else {
		std::cerr << "File copy failed!" << std::endl;
	}
	return 0;
}
