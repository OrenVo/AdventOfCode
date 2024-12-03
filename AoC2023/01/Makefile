
# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -pedantic -Werror -std=c++20 -fopenmp

# Source files
SRCS := main.cpp main_part2.cpp test_main_part2.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable names
TARGET := AoC-01
TARGET2 := AoC-01-02
TEST_TARGET := test

# Default target
all: $(TARGET) $(TARGET2)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executables
$(TARGET): main.cpp
	$(CC) $(CFLAGS) $< -o $@

$(TARGET2): main_part2.cpp
	$(CC) $(CFLAGS) $< -o $@

# Build and run the project
run: all
	./$(TARGET) < input

# Test target using Google Test
test: test_main_part2.o
	$(CC) $(CFLAGS) -pthread $^ -o $(TEST_TARGET) -lgtest -lgtest_main
	./$(TEST_TARGET)

# Clean up object files and executables
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET2) $(TEST_TARGET)

# Debug target
debug: CFLAGS += -g
debug: all

# Default target
all: $(TARGET) $(TARGET2)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): main.cpp
	$(CC) $(CFLAGS) $< -o $@

$(TARGET2): main_part2.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean up object files and executables
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET2)

# Debug target
debug: CFLAGS += -g
debug: all

# Build and run the project
run: all
	./$(TARGET) < input