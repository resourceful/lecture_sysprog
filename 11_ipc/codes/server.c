#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	int FIFO_server,FIFO_client;
	int choice;
	char *buf;

	FIFO_server = open("FIFO-server", O_RDWR);
	if(FIFO_server < 0) {
		fprintf(stderr, "Error opening server side FIFO file");
		exit(-1);
	}

	read(FIFO_server, &choice, sizeof(int));

	sleep(1);

	FIFO_client = open("FIFO-client", O_RDWR);
	if(FIFO_client < 0) {
		fprintf(stderr, "Error opening client side FIFO file");
		exit(-1);
	}
	
	switch(choice) {
		case 1: 
			buf="Linux";
			break;
		case 2:
			buf="Debian";
			break;
		case 3: 
			buf="4.0";
	}

	write(FIFO_client,buf,10*sizeof(char)); 
	printf("\n### Data sent to client ###\n");

	close(FIFO_server);
	close(FIFO_client);
	return 0;
}