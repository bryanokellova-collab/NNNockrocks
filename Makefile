# Compiler
CC = gcc

# Directories
SRC_DIR = src
BUILD_DIR = Build

# Files
SRCS = $(SRC_DIR)/launch.c $(SRC_DIR)/games.c $(SRC_DIR)/Home.c $(SRC_DIR)/banscreen.c $(SRC_DIR)/globals.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Resource file for custom icon
RESOURCE_RC = logo.rc
RESOURCE_OBJ = $(BUILD_DIR)/icon.o

TARGET = $(BUILD_DIR)/Nockrocks.exe

# Libraries and Flags
LIBS = -L$(SRC_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
CFLAGS = -I$(SRC_DIR) -O2

# Declare non-file targets
.PHONY: all build git-commit run clean

# Default target
all: git-commit build

# Build rule
build: $(TARGET)

git-commit:
	git config --global user.name "Fungi"
	git config --global user.email "bryanokellova@gmail.com"
	git add .
	git commit -m "Auto-commit and publish assets before build" || echo "No changes to commit"
	git push origin main || echo "Push failed or already up to date"

# Rule to compile object files individually (Incremental Compilation)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the Windows Icon resource file
$(RESOURCE_OBJ): $(RESOURCE_RC)
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	windres $(RESOURCE_RC) -O coff -o $(RESOURCE_OBJ)

# Link target (Includes the icon resource object and -mwindows for a hidden console)
$(TARGET): $(OBJS) $(RESOURCE_OBJ)
	$(CC) $(OBJS) $(RESOURCE_OBJ) -o $(TARGET) $(LIBS)
	@if exist "$(SRC_DIR)\raylib.dll" copy "$(SRC_DIR)\raylib.dll" "$(BUILD_DIR)\"
	@if exist "Assets" xcopy /E /I /Y "Assets" "$(BUILD_DIR)\Assets"

# Run rule
run: build
	$(TARGET)

# Clean rule
clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"