CC := gcc
SRCS := src/main.c
EXEC := ehdd

compile:
	@./build_helper/set_version.sh
	$(CC) -o $(EXEC) $(SRCS) -Wall -Wextra

gdb:
	@./build_helper/set_version.sh
	$(CC) -o $(EXEC) $(SRCS) -g -Wall -Wextra

install:
	cp ./ehdd /usr/bin/ehdd
