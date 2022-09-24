CC := gcc
SRCS := ehdd.c
EXEC := ehdd

compile:
	$(CC) -o $(EXEC) $(SRCS)

gdb:
	$(CC) -o $(EXEC) $(SRCS) -g

install:
	cp ./ehdd /usr/bin/ehdd
