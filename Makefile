TARGET = robobuddy

CXX = g++

CFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = librobotcontrol.so.1

all:
	$(CXX) $(CFLAGS) -l:$(LDFLAGS) main.cpp -o $(TARGET)
	./$(TARGET)
