# Makefile for cli_pwd.cpp

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra #g to enable gdb (start; s to step into; n to step over; p to print a variable value)

# Source files
SOURCES = cli_pwd.cpp manager.cpp Encrypt.cpp helper.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = manager.h Encrypt.h pwd.h helper.hh

# Target executable
TARGET = clipwd

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)
