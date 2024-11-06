#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
bool copy_file(const std::string& source, const std::string& dest);
void log_action(const std::string& message);

#endif // FILEUTILS_H

