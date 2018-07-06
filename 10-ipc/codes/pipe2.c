#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define	MAXLINE	4096			/* max line length */
#define	DEF_PAGER	"/usr/bin/more"		/* default pager program */

int
main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if (argc != 2){
		fprintf(stderr, "usage: a.out <pathname>");
		exit(1);
	}

	if ((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "can't open %s", argv[1]);
		exit(1);
	}
	if (pipe(fd) < 0){
		fprintf(stderr, "pipe error");
		exit(1);
	}

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error");
		exit(1);
	} else if (pid > 0) {								/* parent */
		close(fd[0]);		/* close read end */

		/* parent copies argv[1] to pipe */
		while (fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				fprintf(stderr, "write error to pipe");
		}
		if (ferror(fp))
			fprintf(stderr, "fgets error");

		close(fd[1]);	/* close write end of pipe for reader */

		if (waitpid(pid, NULL, 0) < 0){
			fprintf(stderr, "waitpid error");
			exit(1);
		}
		exit(0);
	} else {										/* child */
		close(fd[1]);	/* close write end */
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
				fprintf(stderr, "dup2 error to stdin");
				exit(1);
			}
			close(fd[0]);	/* don't need this after dup2 */
		}

		/* get arguments for execl() */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* step past rightmost slash */
		else
			argv0 = pager;	/* no slash in pager */

		if (execl(pager, argv0, (char *)0) < 0){
			fprintf(stderr, "execl error for %s", pager);
			exit(1);
		}
	}
	exit(0);
}
