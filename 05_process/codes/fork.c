#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int gvar = 6;   // external variable in initialized data
char buf[] = "a write to stdout\n";

int
main(int argc, char **argv) {
	int var;    // automatic variable on the stack
	pid_t pid;

	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
		fprintf(stderr, "%s: write error: %s\n", argv[0], strerror(errno));
		exit(1);
	}
	printf("before fork\n"); // we don't flush stdout

	if ((pid = fork()) < 0) {
		fprintf(stderr, "%s: fork error: %s\n", argv[0], strerror(errno));
		exit(1);
	} else if (pid == 0) { // child 
		gvar++;            // modify variables
		var++;
	} else {		// parent 
		sleep(2);
	}

	printf("pid = %d, gvar = %d, var = %d\n", getpid(), gvar, var);
	exit(0);
}
