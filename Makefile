# Compiler settings
CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LDFLAGS = -lws2_32

# Define directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Define the target executable
TARGET = $(BIN_DIR)/myServer.exe

# Find all the C++ files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)

# Generate the object file names
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default rule to build the project
all: build $(TARGET)

$(TARGET): $(OBJECTS)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule to build the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $<
	@powershell -Command "$$dir = '$(@D)'; if (-Not (Test-Path $$dir)) { New-Item -ItemType Directory -Path $$dir | Out-Null }"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to clean up the workspace
clean:
	if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"

# Rule to create the build directory
build:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(OBJ_DIR)\Server" mkdir "$(OBJ_DIR)\Server"


# @if not exist "$(OBJ_DIR)\Http" mkdir "$(OBJ_DIR)\Http"