CC=gcc
CFLAGS=-I.

all: server client

server: server.c
	$(CC) multmodulo.c server.c -o server.o  -lpthread $(CFLAGS)

client: client.c
	$(CC) multmodulo.c client.c -o client.o  -lpthread $(CFLAGS)

libs: multmodulo.c
	$(CC) -c multmodulo.c -o multmodulo.o
	ar rcs librepetition.a multmodulo.o

clean :
	rm client.out server.out