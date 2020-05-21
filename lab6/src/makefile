CC=gcc
CFLAGS=-I.

all: server client

server: server.c
	$(CC) server.c libmulti.so -lpthread -o server.o $(CFLAGS)

client: client.c
	$(CC) client.c libmulti.so -lpthread -o client.o $(CFLAGS)

clean :
	rm client.o server.o