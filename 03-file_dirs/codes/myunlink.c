#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
	if (open("tempfile", O_RDWR) < 0){
		fprintf(stderr, "open error");
		exit(EXIT_FAILURE);
	}

	if (unlink("tempfile") < 0){
		fprintf(stderr, "unlink error");
		exit(EXIT_FAILURE);
	}

	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}
