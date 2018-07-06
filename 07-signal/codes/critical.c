#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void
sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR){
		fprintf(stderr, "can't reset SIGQUIT");
		exit(1);
	}
}

int
main(void)
{
	sigset_t	newmask, oldmask, pendmask;

	printf("C-\\ to generate SIGQUIT signal\n");

	// Add user function sig_quit fro SIGQUIT
	if (signal(SIGQUIT, sig_quit) == SIG_ERR){
		fprintf(stderr, "can't catch SIGQUIT");
		exit(1);
	}

	/*
	 * Block SIGQUIT and save current signal mask.
	 */
	sigemptyset(&newmask); // empty the signal set
	sigaddset(&newmask, SIGQUIT); // add SIGQUIT signal to newmask

	// oldmask saves current signal mask for the process	
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		fprintf(stderr, "SIG_BLOCK error");
		exit(1);
	}

	sleep(5);	/* SIGQUIT here will remain pending */

	// return signals that are blocked from delivery and currently pending for the calling process
	if (sigpending(&pendmask) < 0){
		fprintf(stderr, "sigpending error");
		exit(1);
	}
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	/*
	 * Restore signal mask which unblocks SIGQUIT.
	 * we could use SIG_UNBLOCK.
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		fprintf(stderr, "SIG_SETMASK error");
		exit(1);
	}
	printf("SIGQUIT unblocked\n");

	printf("C-\\ to generate SIGQUIT signal again\n");
	sleep(5);	/* SIGQUIT here will terminate with core file */
	exit(0);
}


