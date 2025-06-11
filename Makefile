# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = tests

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
MAIN_SRC = $(SRC_DIR)/main.c
LIB_SRCS = $(filter-out $(MAIN_SRC), $(SRCS))

# Object files
MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(MAIN_SRC))
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))

# Binaries
TARGET = $(BUILD_DIR)/pinc

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/tests/%.o, $(TEST_SRCS))
TEST_BIN = $(BUILD_DIR)/run_tests

# Default build target
all: $(TARGET) $(TEST_BIN)

# Main build rule
$(TARGET): $(MAIN_OBJ) $(LIB_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

# Build rule for src object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Test build rule
$(TEST_BIN): $(TEST_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(SRC_DIR)/internal -o $@ $^

# Build rule for test object files
$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)/tests
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(SRC_DIR)/internal -c $< -o $@

# Create build directories if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/tests:
	mkdir -p $(BUILD_DIR)/tests

# Run targets
run: $(TARGET)
	./$(TARGET)

test: $(TEST_BIN)
	./$(TEST_BIN)

# Clean build
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run test

