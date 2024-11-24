CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = do-command
SRCS = do-command.cpp
OBJS = $(SRCS:.cpp=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
.PHONY: all clean
