CC = g++
CFLAGS = -std=c++11 -Wall -Wextra

.PHONY: all clean

all: subscriber server

subscriber: subscriber.cpp
	$(CC) $(CFLAGS) -o subscriber subscriber.cpp

server: server.cpp
	$(CC) $(CFLAGS) -o server server.cpp

run_subscriber: subscriber
	./subscriber

run_server: server
	./server

clean:
	rm -f subscriber server