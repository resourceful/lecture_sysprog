#include    <stdio.h>
#include    <stdlib.h>
#include    <errno.h>
#include    <unistd.h>
#include    <sys/wait.h>

int
system(const char *cmdstring) /* version without signal handling */
{
	pid_t   pid;
	int     status;

	if (cmdstring == NULL)
		return(1);      /* always a command processor with UNIX */
	if ((pid = fork()) < 0) {
		status = -1;    /* probably out of processes */
	} else if (pid == 0) {              /* child */
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);     /* execl error */
	} else {                            /* parent */
		while (waitpid(pid, &status, 0) < 0) {
			if (errno != EINTR) {
				status = -1; /* error other than EINTR from waitpid() */
				break;
			} 
		}
	}
	return(status);
}


void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef  WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
#else
				"");
#endif
    else if (WIFSTOPPED(status))
		printf("child stopped, singal number = %d\n", WSTOPSIG(status));
}


int
main(int argc, char **argv)
{
	int status;
	if ((status = system("date")) < 0)
		fprintf(stderr, "system() error");

	pr_exit(status);

	if ((status = system("nosuchcommand")) < 0)
		fprintf(stderr, "system() error");

	pr_exit(status);

	if ((status = system("who; exit 44")) < 0)
		fprintf(stderr, "system() error");

	pr_exit(status);

	exit(0); 
}
