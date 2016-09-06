/*
 * APUE Figure 1.6
 * This trivial program simply prints out its own PID and exits.
 * Usage: ./pid
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv) {
	printf("Hello world from process id %d\n", getpid());
	return(0);
}
