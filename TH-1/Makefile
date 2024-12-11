# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -pthread

# Output binary
TARGET = array-summary

# Source files
SRCS = array-summary.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# All target
all: $(TARGET)

# Link the target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)
