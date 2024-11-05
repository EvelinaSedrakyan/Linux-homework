# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Имя выходного исполнимого файла
TARGET = read-file

# Исходные файлы
SRC = read-file.cpp

# Объектные файлы
OBJ = $(SRC:.cpp=.o)

# Целевая задача по умолчанию
all: $(TARGET)

# Линковка объектных файлов в исполнимый файл
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Компиляция исходных файлов в объектные
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка объектных файлов и исполнимого файла
clean:
	rm -f $(OBJ) $(TARGET)
