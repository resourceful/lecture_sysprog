#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
	int server, client;

	/* create a FIFO for server */
	server = mkfifo("FIFO-server", 0666); 
	if(server < 0) {
		fprintf(stderr, "Failed to create a FIFO for server");
		exit(-1);
	}

	/* create a FIFO for client */
	client = mkfifo("FIFO-client", 0666);
	if(client < 0) {
		fprintf(stderr, "Failed to create a FIFO for client");
		exit(-1);
	}

	printf("FIFO for server and child created successfuly");

	return 0;
}