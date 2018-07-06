#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAXPATHLEN	512

int
main(int argc, char **argv)
{
	char buf[MAXPATHLEN];

	if (argc != 2) {
		fprintf(stderr, "%s: requires a directory!\n", argv[0]);
		return(EXIT_FAILURE);
	}

	if (chdir(argv[1]) < 0) {
		fprintf(stderr, "%s: unable to change directory to %s\n", 
						argv[0], argv[1]);
		return(EXIT_FAILURE);
	}

	printf("CWD is now: %s\n", getcwd(buf, MAXPATHLEN));

	if (system("ls -l") != 0) {
		perror("unable to run ls(1)");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}
