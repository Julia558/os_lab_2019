all: tcp udp

tcp: tcpclient tcpserver

udp: udpclient udpserver

tcpserver: tcpserver.c
	gcc tcpserver.c -o tcpserver.o

tcpclient: tcpclient.c
	gcc tcpclient.c -o tcpclient.o

udpserver: udpserver.c
	gcc udpserver.c -o udpserver.o

udpclient: udpclient.c
	gcc udpclient.c -o udpclient.o

clean:
	rm *.o