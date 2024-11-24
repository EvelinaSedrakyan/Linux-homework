# Переменные
CC = g++
CFLAGS = -Wall -std=c++11
TARGET = interactive-shell
SOURCES = interactive-shell.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Цель по умолчанию
all: $(TARGET)

# Правило для создания исполнимого файла
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Правило для компиляции исходников в объектные файлы
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка объектных файлов и исполнимого файла
clean:
	rm -f $(OBJECTS) $(TARGET)
