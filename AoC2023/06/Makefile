
# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -pedantic -Werror -std=c++20 -fopenmp

# Source files
SRCS := main.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := AoC-06

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Debug target
debug: CFLAGS += -g
debug: all

# Build and run the project
run: all
	./$(TARGET) < input

