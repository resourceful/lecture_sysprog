#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define	MAXLINE	4096			/* max line length */

int
main(void)
{
	char	line[MAXLINE];
	FILE	*fpin;

	if ((fpin = popen("./myuclc", "r")) == NULL){
		fprintf(stderr, "popen error");
		exit(1);
	}

    /* type 111 to exit the program */
	while (strcmp(line, "111\n") != 0){
		fputs("prompt> ", stdout);
		fflush(stdout);
		if (fgets(line, MAXLINE, fpin) == NULL)	/* read from pipe */
			break;
		if (fputs(line, stdout) == EOF)
			fprintf(stderr, "fputs error to pipe");
	}
	if (pclose(fpin) == -1){
		fprintf(stderr, "pclose error");
		exit(1);
	}
	putchar('\n');
	exit(0);
}
