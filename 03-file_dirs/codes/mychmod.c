/* 
 * Set umask to 077 and touch foo foo1, then run this command.
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
	struct stat statbuf;

	/* turn on set-group-ID and turn off group-execute */
	if ( stat("foo", &statbuf) < 0 ) {
		fprintf(stderr, "can't stat foo\n");
		exit(EXIT_FAILURE);
	}

	/* turn off group execute and turn on set-UID */
	if ( chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISUID) == -1 ) {
		fprintf(stderr, "can't chmod foo\n");
		exit(EXIT_FAILURE);
	}

	/* set absolute mode to rw-r--r-- */
	if ( chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1 ) {
		fprintf(stderr, "can't chmod bar\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
