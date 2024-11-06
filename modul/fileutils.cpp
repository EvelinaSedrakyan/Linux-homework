#include "fileutils.h"
#include <fstream>
#include <iostream>
#include <sstream>
bool copy_file(const std::string& source, const std::string& dest) {
	std::ifstream src(source, std::ios::binary);
	if (!src) {
		log_action("Failed to open source file: " + source);
		return false;
	}
	std::ofstream dst(dest, std::ios::binary);
	if (!dst) {
		log_action("Failed to open destination file: " + dest);
		return false;
	}
	dst << src.rdbuf(); 
	log_action("File copied from " + source + " to " + dest);
	return true;
}

void log_action(const std::string& message) {
	std::ofstream log("log-file.txt", std::ios::app);
	if (!log) {
		std::cerr << "Failed to open log file." << std::endl;
		return;
	}
	log << message << std::endl;
}

