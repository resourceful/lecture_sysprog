#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>

// change the user name
#ifndef USER
#define USER "James"
#endif

static void
my_alarm(int signo)
{
	struct passwd *rootptr;

	write(STDOUT_FILENO, "in signal handler\n", 18);
	if ((rootptr = getpwnam("root")) == NULL){
		write(STDERR_FILENO, "getpwnam(root) error\n", 21);
		exit(1);
	}
	alarm(1);
}

int
main(void)
{
	struct passwd *ptr;

	if (signal(SIGALRM, my_alarm) == SIG_ERR) {
		fprintf(stderr, "Unable to establish signal handler: %s\n", strerror(errno));
		exit(1);
	}
	alarm(1);
	for ( ; ; ) {
		if ((ptr = getpwnam(USER)) == NULL){
			fprintf(stderr, "user %s not found, getpwnam error\n", USER);
			exit(1);
		}
		if (strcmp(ptr->pw_name, USER) != 0){
			fprintf(stderr, "return value corrupted!, pw_name = %s\n",
					ptr->pw_name);
			abort();
		}
	}
}
