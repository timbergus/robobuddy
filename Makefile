CXX=clang++-7

TARGET=robobuddy

ROOT=src
APP=$(ROOT)/app
INCLUDE=$(ROOT)/include
BIN=bin

CFLAGS=-std=c++2a -Werror -Wall -Wextra
IFLAGS=-I $(INCLUDE) -I /var/lib/cloud9/gustavo/gps-playground/src/include -I /usr/local/include
LFLAGS=-L /usr/local/lib -l:librobotcontrol.so.1

OBJS=$(BIN)/main.o

$(BIN)/%.o: $(INCLUDE)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

$(BIN)/%.o: $(APP)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

$(TARGET): $(OBJS)
	@$(CXX) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

-include $(BIN)/*.d

start:
	@$(BIN)/$(TARGET)

.PHONY: clean

clean:
	rm -r $(BIN)
