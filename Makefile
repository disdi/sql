# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I./include -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Main programs
MAIN_SRCS = main.c
MAIN_OBJS = $(MAIN_SRCS:%.c=$(OBJ_DIR)/%.o)
MAIN_PROG = $(BIN_DIR)/database

# All executables
ALL_PROGS = $(MAIN_PROG) $(TEST_PROG)

# Default target
all: directories $(ALL_PROGS)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Main program
$(MAIN_PROG): $(OBJS) $(MAIN_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main file
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Clean and rebuild
rebuild: clean all

# Install (optional, adjust install location as needed)
install: all
	install -d $(DESTDIR)/usr/local/bin
	install -m 755 $(MAIN_PROG) $(DESTDIR)/usr/local/bin

# Generate dependency files
depend: $(SRCS)
	$(CC) $(CFLAGS) -MM $^ | sed 's/^\(.*\)\.o:/$(OBJ_DIR)\/\1.o:/' > Makefile.dep

# Include dependencies
-include Makefile.dep

# Phony targets
.PHONY: all clean rebuild install directories depend