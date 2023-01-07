CC := gcc
SRCS := src/main.c
EXEC := ehdd

compile:
	@./build_helper/set_version.sh
	$(CC) -o $(EXEC) $(SRCS) -Wall -Wextra
	@./build_helper/clean.sh

gdb:
	@./build_helper/set_version.sh
	$(CC) -o $(EXEC) $(SRCS) -g -Wall -Wextra
	@./build_helper/clean.sh

install:
	cp ./ehdd /usr/bin/ehdd
