#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 100

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *shm;
	char *s;
	char *message = "The client sends a reply0";

	// generate key
	if( (key = ftok("Makefile", 'R')) == -1 )
	{
		perror("ftok");
		exit(1);
	}

	// connect to the segment
	if ( (shmid = shmget( key, SHSIZE, 0666 )) < 0 )
	{
		perror( "shmget" );
		exit(1);
	}

	// attach to the segment to get a pointer to it
	if ( (shm = shmat( shmid, NULL, 0 )) == (char *) -1 )
	{
		perror( "shmat" );
		exit(1);
	}


	printf("Reading server side message from Shared Memory\n");
	sleep(1);

	// read shared memory
	for( s = shm ; *s != '0' ; s++ )
		printf( "%c", *s );

	printf( "\n" ); 


	printf("Terminating the program\n");
	sleep(1);
	// generate termination condition
	*shm = '*';

	sleep(1);

	printf("Client sends a message back\n");
	memcpy( shm, message, strlen(message) );
	sleep(2);
	return 0;
}