# This is the compiler.
CXX=g++

# These are the flags.
CFLAGS=-c -std=c++17 -Wall -Wextra
LDFLAGS=

# These are the source files.
SOURCES=src/main.cpp src/parsers/gnrmc.cpp src/utils.cpp
OBJECTS=$(SOURCES:.cpp=.o)

# Executable.
EXECUTABLE=output/nmea_parser

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm output/nmea_parser $(OBJECTS)
