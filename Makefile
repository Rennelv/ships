# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRC_DIR = src
MODULES_DIR = src/modules
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/main.cpp \
	   $(MODULES_DIR)/Ship.cpp \
	   $(MODULES_DIR)/ShipField.cpp \
	   $(MODULES_DIR)/ShipManager.cpp

# Object files
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Executable
TARGET = battleship

# Default target
all: $(BUILD_DIR) $(TARGET)

# Debug target
debug: CXXFLAGS += -g
debug: $(BUILD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@echo "Creating build directories..."
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	mkdir -p $(BUILD_DIR)/$(MODULES_DIR)


# Link the executable
$(TARGET): $(OBJS)
	@echo "Linking executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build files
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean