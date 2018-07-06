#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char *buf;
	int choice = 1;
	int fifo_server, fifo_client;

	printf("Chose one of following options to send to the server\n");
	printf("\t\t 1 for the name of the OS \n \
	         2 for the name of distribution \n \
	         3 for the version of Kernel \n");
	printf("Your choice: ");
	scanf("%d",&choice);

	fifo_server=open("FIFO-server",O_RDWR);
	if(fifo_server < 0) {
		 fprintf(stderr, "Error in opening file");
		 exit(-1);
	 }

	write(fifo_server, &choice, sizeof(int));

	fifo_client=open("FIFO-client", O_RDWR);
	
	if(fifo_client < 0) {
		 fprintf(stderr, "Error in opening file");
		 exit(-1);
	 }

	buf=malloc(10*sizeof(char));
	read (fifo_client, buf, 10*sizeof(char));
	printf("\n ### Server replied with %s ###\n", buf);

	close(fifo_server);
	close(fifo_client);
	return 0;
}
