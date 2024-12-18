CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
LDFLAGS =

TARGET = signal-echo
OBJFILES = signal-echo.o

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJFILES)
