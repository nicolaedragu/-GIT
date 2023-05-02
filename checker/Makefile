CC = gcc
CFLAGS = -Wall -g

build: quadtree

quadtree: quadtree.o
	$(CC) -o quadtree $^ 

quadtree.o: quadtree.c
	$(CC) $(CFLAGS) -c $^

run: build
	./quadtree

clean:
	rm -f *.o quadtree