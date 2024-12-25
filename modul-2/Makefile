CC = g++
CFLAGS = -std=c++11 -pthread
TARGET = find-max

all: $(TARGET)

$(TARGET): find-max.cpp
	$(CC) $(CFLAGS) -o $(TARGET) find-max.cpp

clean:
	rm -f $(TARGET)
