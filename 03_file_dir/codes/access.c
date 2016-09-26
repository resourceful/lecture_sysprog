#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "%s: Usage: %s filename\n", argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], R_OK) < 0)
		printf("access error for %s\n", argv[1]);
	else
		printf("access OK for %s\n", argv[1]);


	if (open(argv[1], O_RDONLY) < 0)
		printf("open error for %s\n", argv[1]);
	else
		printf("open for reading OK: %s\n", argv[1]);

	exit(EXIT_SUCCESS);
}
