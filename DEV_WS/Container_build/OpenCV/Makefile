# Compiler :
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Use pkg-config properly
PKG_CFLAGS := $(shell pkg-config --cflags opencv4)
PKG_LIBS   := $(shell pkg-config --libs opencv4)

# Directories :
SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
BUILD_DIR := build

# Target :
TARGET := $(BIN_DIR)/camera_test

# Source files :
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files :
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Header dependencies :
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Default target :
all: $(TARGET)

# Link the executable :
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(PKG_LIBS)
	@echo "Build successful! Executable at $(TARGET)"
	@echo "----------------------------------------"

# Compile source files into objects :
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PKG_CFLAGS) -I$(INC_DIR) -c $< -o $@

# Create directories if not exist :
$(BIN_DIR) $(BUILD_DIR):
	@mkdir -p $@

# Run the program :
run: $(TARGET)
	./$(TARGET)

# Clean the build :
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)
	@echo "Clean complete."
	@echo "----------------------------------------"

# Help :
help:
	@echo "Available Targets:"
	@echo "-----------------"
	@echo "|----------------------------------------|"
	@echo "| make all   - Build the project         |"
	@echo "| make clean - Clean the project         |"
	@echo "| make run   - Build and run the project |"
	@echo "| make help  - Show help messages        |"
	@echo "|----------------------------------------|"

.PHONY: all run clean help
