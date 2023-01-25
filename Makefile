CC := gcc
SRCS := src/main.c
EXEC := ehdd

compile:
	@./build_helper/local/init.sh
	$(CC) -o $(EXEC) $(SRCS) -Wall -Wextra -Os
	@./build_helper/local/clean.sh

gdb:
	@./build_helper/local/init.sh
	$(CC) -o $(EXEC) $(SRCS) -g -Wall -Wextra
	@./build_helper/local/clean.sh

install:
	cp ./ehdd /usr/bin/ehdd
