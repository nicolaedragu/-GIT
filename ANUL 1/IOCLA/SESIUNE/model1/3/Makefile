CFLAGS = -Wall -Wextra -m32 -Iinclude -fno-stack-protector -mpreferred-stack-boundary=2 -fno-PIC
LDFLAGS = -m32 -no-pie

# TODO: complete the Makefile to make the linking work

all: main.o file.o test.o directory.o
	$(CC) $(CFLAGS) $^ -o main

