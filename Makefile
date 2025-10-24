# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -Iinclude

# Project name
TARGET = main

# Directories
SRC_DIR = src
OBJ_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default rule
all: release

# Release build (optimized)
release: CXXFLAGS += -O3
release: $(TARGET)

# Debug build (no optimization, with debug symbols)
debug: CXXFLAGS += -O0 -g -DDEBUG
debug: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp into .o (object) files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p $(OBJ_DIR)

# Remove build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the program (uses release by default)
run: release
	./$(TARGET)

.PHONY: clean run all release debug
