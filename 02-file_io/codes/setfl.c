/* simple-cat.c
 * Stripped down version of 'cat'.
 */

#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 512

int
main(int argc, char **argv)
{
	int n, c;
	char buf[BUFFSIZE];
	int flags;
	int osync_on = 0, fsync_on = 0, fdatasync_on = 0;

	if (argc < 2){
		printf("usage: %s -{a|b|c|d} < LARGEFILE_IN > LARGEFILE_OUT \n", argv[0]);
		printf (" -a for add O_SYNC flag\n");
		printf (" -b for removing O_SYNC flag\n");
		printf (" -c for add fsync call\n");
		printf (" -d for add fdatasync call (doesnot work in OSX)\n");
		return 0;
	}
	while (( c = getopt (argc, argv, "abcdh")) != -1){
		switch (c){
			case 'a':
				printf("O_SYNC is on\n");
				osync_on = 1;
				break;
			case 'b':
				printf("O_SYNC is off\n");
				osync_on = 0;
				break;
			case 'c':
				printf("O_SYNC is off, writes are followed by fsync\n");
				fsync_on = 1;
				break;
			case 'd':
				printf("O_SYNC is off, writes are followed by fdatasync\n");
				fdatasync_on = 1;
				break;
			case 'h':
				printf("usage: %s -{a|b|c|d} < LARGEFILE_IN > LARGEFILE_OUT \n", argv[0]);
				printf ("Options are a, b, c, d\n");
				printf (" -a for add O_SYNC flag\n");
				printf (" -b for removing O_SYNC flag\n");
				printf (" -c for add fsync call\n");
				printf (" -d for add fdatasync call (doesnot work in OSX)\n");
				return 0;
			case '?':
				if (isprint(optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option `\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}
	}	
	if ((flags = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0) {
		perror("Can't get file descriptor flags");
		exit(1);
	}

	if (osync_on == 1)
		flags |= O_SYNC;


	if (fcntl(STDOUT_FILENO, F_SETFL, flags) < 0) {
		perror("Can't set file descriptor flags");
		exit(1);
	}

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0 ){
		if ( write(STDOUT_FILENO, buf, n) != n ) {
			fprintf(stderr, "write error\n");
			exit(1);
		}
		if (fsync_on == 1)
			fsync(STDOUT_FILENO);
#ifdef __APPLE__
// fdatsync doesnot work on osx
#else
		if (fdatasync_on == 1)
			fdatasync(STDOUT_FILENO);
#endif
	}

	if (n < 0) {
		fprintf(stderr, "read error\n");
		exit(1);
	}

	exit(0);
}
