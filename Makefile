# Makefile for guniq program

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Name of the output executable
TARGET = guniq.x

# Source files
SOURCES = main.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Rule for building the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for creating object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean target for removing generated files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets
.PHONY: all clean