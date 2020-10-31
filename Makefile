# Executable.
EXECUTABLE = output/robobuddy

# This is the compiler.
CXX = g++

# These are the flags (we are using the latest c++ version).
CFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = librobotcontrol.so.1

# Source files.
SOURCES = src/main.cpp src/utils.cpp src/gnrmc.cpp

all:
	$(CXX) $(CFLAGS) -l:$(LDFLAGS) $(SOURCES) -o $(EXECUTABLE) -I./src
	# $(CXX) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) -I./src
	./$(EXECUTABLE)
