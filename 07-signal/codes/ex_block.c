#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int do_block = 0; //toggle
int signum; // received signal

void
hup_handler(int sig) { //hangup signal handler
    signum = sig;
}

void
int_handler(int sig) { //toggle do_block
    signum = sig;
    do_block = !do_block;
}

int
main() {
    sigset_t signal_set;

    // Install signal handler.
    signal(SIGHUP, hup_handler); // hangup
    signal(SIGINT, int_handler); // interrupt

    sigemptyset(&signal_set);   // empty set of signal_set
    sigaddset(&signal_set, SIGHUP); // add signal hang up to set

    while (1) {
        if (do_block) // if true block signal_set
            sigprocmask(SIG_BLOCK, &signal_set, NULL);
        else // if not unblock signal_set
            sigprocmask(SIG_UNBLOCK, &signal_set, NULL);
        sleep(1000);
        printf("Process received signal %d\n", signum);
    }
}
