#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main( int argc, char **argv ) {
	int pid = fork();
	if ( pid == 0 )
		execvp( "./sequential.o", argv );
    int status;
    wait(&status);
	return 0;
}