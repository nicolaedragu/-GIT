CC = gcc
CFLAGS = -Wall -g

build: tema3
	touch tema3.out

tema3: tema3.o
	$(CC) -o tema3 $^

tema3.o: tema3.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o tema3