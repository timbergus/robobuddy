CC=clang++-7
CFLAGS=-std=c++17 -Werror -Wall -Wextra
IFLAGS=-I $(INCLUDE) -I /usr/local/include
LFLAGS=-L /usr/local/lib -l:librobotcontrol.so.1

TARGET=robobuddy
ROOT=src/app
INCLUDE=src/include
BIN=src/bin

OBJS=	$(BIN)/main.o	\
		$(BIN)/gnrmc.o	\
		$(BIN)/utils.o

$(BIN)/%.o: $(INCLUDE)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

$(BIN)/%.o: $(ROOT)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

-include $(BIN)/*.d

start:
	@$(BIN)/$(TARGET)

.PHONY: clean

clean:
	rm -r $(BIN)
