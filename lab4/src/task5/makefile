CC=gcc
CFLAGS=-I.

all : parallel_sum.c sum.c utils.c
	gcc -c sum.c -o sum.o
	gcc -shared sum.o -o libsum.so
	gcc parallel_sum.c utils.c -L. -lsum -lpthread -o sum

clean :
	rm sum.o sum libsum.so sum_