#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define	MAXLINE	4096			/* max line length */
#define	PAGER	"${PAGER:-more}" /* environment variable, or default */

int
main(int argc, char *argv[])
{
	char	line[MAXLINE];
	FILE	*fpin, *fpout;

	if (argc != 2){
		fprintf(stderr, "usage: a.out <pathname>");
		exit(1);
	}
	if ((fpin = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "can't open %s", argv[1]);
		exit(1);
	}

	if ((fpout = popen(PAGER, "w")) == NULL){
		fprintf(stderr, "popen error");
		exit(1);
	}

	/* copy argv[1] to pager */
	while (fgets(line, MAXLINE, fpin) != NULL) {
		if (fputs(line, fpout) == EOF){
			fprintf(stderr, "fputs error to pipe");
			exit(1);
		}
	}
	if (ferror(fpin)){
		fprintf(stderr, "fgets error");
		exit(1);
	}
	if (pclose(fpout) == -1){
		fprintf(stderr, "pclose error");
		exit(1);
	}

	exit(0);
}
