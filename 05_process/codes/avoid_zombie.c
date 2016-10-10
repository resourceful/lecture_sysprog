#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
	pid_t pid;
	printf("this is parent, pid = %d\n", getpid());
	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error");
	} else if (pid == 0) {
			if ((pid = fork()) < 0)       /* first child */
				fprintf(stderr, "fork error");
			else if (pid > 0){
				printf("this is first child(%d) exiting\n", getpid());
				exit(0);    /* parent from second fork == first child */
			}
		/*
		 * We’re the second child; our parent becomes init as soon
		 * as our real parent calls exit() in the statement above.
		 * Here’s where we’d continue executing, knowing that when
		 * we’re done, init will reap our status.
		 */
		sleep(2);
		printf("second child(%ld), parent pid = %ld\n", 
				(long)getpid(), (long)getppid());
		exit(0);
	}

	printf("this is parent(%d) waiting for child %d\n", getpid(), pid);
	if (waitpid(pid, NULL, 0) != pid)   /* wait for first child */
        fprintf(stderr, "waitpid error");
    /*
     * We’re the parent (the original process); we continue executing,
     * knowing that we’re not the parent of the second child.
     */
	exit(0); 
}