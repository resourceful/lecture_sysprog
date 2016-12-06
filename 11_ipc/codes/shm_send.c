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
	char *shm, *s;
	char *message = "The server sends a line of text0";

	// generate key
	if ( (key = ftok("Makefile", 'R')) == -1 )
	{
		perror("ftok");
		exit(1);
	}

	// connect to the segment
	if ( (shmid = shmget( key, SHSIZE, IPC_CREAT | 0666 )) < 0 )
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

	// modify segment
	memcpy( shm, message, strlen(message) );

	printf("Server side message is: %s\n", message);
	printf("Waiting for Client to change the memory\n");

	// Wait for termination condition
	while( *shm != '*' )
		sleep( 1 );

	sleep (1);
	printf("\nClient changed the memory, and the message is: \n");
	for( s = shm ; *s != '0' ; s++ )
		printf( "%c", *s );


	sleep( 1 );

	return 0;
}