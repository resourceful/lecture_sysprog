#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char    *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int
main(int argc, char **argv)
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
	} else if (pid == 0) {  /* specify pathname, specify environment */
		if (execle("/Users/James/_projects/class_systemProgramming_2016/lecture_sysprog/05_process/codes/echoall", "echoall", "myarg1",
					"MY ARG2", (char *)0, env_init) < 0){
			fprintf(stderr, "execle error\n");
			printf("####  First fork ended\n");
		}
	}

	if (waitpid(pid, NULL, 0) < 0)
		fprintf(stderr, "wait error\n");

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
	} else if (pid == 0) {  /* specify filename, inherit environment */
		if (execlp("./echoall", "echoall", "only 1 arg", (char *)0) < 0)
			fprintf(stderr, "execlp error\n");
	}

	exit(0); 
}