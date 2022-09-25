CC := gcc
SRCS := ehdd.c
EXEC := ehdd

compile:
	$(CC) -o $(EXEC) $(SRCS) -Wall -Wextra

gdb:
	$(CC) -o $(EXEC) $(SRCS) -g -Wall -Wextra

install:
	cp ./ehdd /usr/bin/ehdd
