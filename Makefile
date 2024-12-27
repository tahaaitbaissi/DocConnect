# Compiler and Flags
CXX = g++
CXXFLAGS = -std=gnu++1z -Iinclude -Wall -Wextra -Werror -L/usr/lib/oracle/23/client64/lib -lclntsh
LDFLAGS = -L/usr/lib/oracle/23/client64/lib -lclntsh  # Link Oracle OCI library

# Directories
SRC_DIR = app
BUILD_DIR = build
INCLUDE_DIR = include

# Find All Source Files Recursively in the SRC_DIR
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp") main.cpp
OBJ_FILES = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRC_FILES)))

# Target Executable
TARGET = DocConnect

# Default Rule
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $@

# Compile Source Files to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Handle Source Files from Subdirectories
$(BUILD_DIR)/%.o: $(SRC_DIR)/*/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Build Directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
