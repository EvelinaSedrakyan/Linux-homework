# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Имя выходного исполнимого файла
TARGET = manual-append

# Исходные файлы
SRC = manual-append.cpp

# Объектные файлы
OBJ = $(SRC:.cpp=.o)

# Цель по умолчанию (сборка программы)
all: $(TARGET)

# Линковка объектных файлов в исполнимый файл
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Компиляция исходных файлов в объектные
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка объектных и исполнимых файлов
clean:
	rm -f $(OBJ) $(TARGET)
