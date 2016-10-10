#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static void charatatime(char *str);

int
main(int argc, char **argv)
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error");
	} else if (pid == 0) {
		charatatime("output from child\n");
	} else {
		charatatime("this is parent\n");
	}
	exit(0); 
}
static void
charatatime(char *str)
{
	char    *ptr;
	int     c;
	setbuf(stdout, NULL);    /* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; ){
		putc(c, stdout);
	}
}


