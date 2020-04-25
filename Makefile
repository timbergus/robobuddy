# This is the compiler.
CXX=g++

# These are the flags.
CFLAGS=-std=c++17 -Wall -Wextra
LDFLAGS=librobotcontrol.so.1

# Executable.
EXECUTABLE=robobuddy

all:
    $(CXX) $(CFLAGS) -l:$(LDFLAGS) main.cpp -o output/$(EXECUTABLE)
    ./output/$(EXECUTABLE)
