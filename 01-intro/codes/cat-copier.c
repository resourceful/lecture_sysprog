/*
 * APUE Figure 1.5
 * Stripped down version of 'cat', buffered version.
 * Guess what, this is also a primitive version of 'cp':
 * Usage: ./cat-copier < ANY_FILE > OUTPUT_FILE
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv) {
	int c;

	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF) {
			fprintf(stderr, "write error\n");
			exit(1);
		}

	if (ferror(stdin)) {
		fprintf(stderr, "read error\n");
		exit(1);
	}

	return(0);
}
