#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int
main(int argc, char **argv)
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
	} else if (pid == 0) { /* child */
		if (execl("/Users/James/_projects/class_systemProgramming_2016/lecture_sysprog/05_process/codes/testinterp",
		//if (execl("echoarg",
			"testinterp", "myarg1", "MY ARG2", (char *)0) < 0)
		fprintf(stderr, "execl error (%d)\n", errno);
	}
	if (waitpid(pid, NULL, 0) < 0)  /* parent */
		fprintf(stderr, "waitpid error\n");
	exit(0);
}