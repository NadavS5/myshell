# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Icommands -Iutils

# Source files
SRC = shell.cpp $(wildcard commands/*.cpp) $(wildcard utils/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Output executable
TARGET = shell.exe

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
# 	@rm -f $(OBJ)
# Compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
