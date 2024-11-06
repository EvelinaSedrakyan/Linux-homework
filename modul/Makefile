CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = program
SRC = main.cpp fileutils.cpp
OBJ = $(SRC:.cpp=.o)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f log-file.txt
