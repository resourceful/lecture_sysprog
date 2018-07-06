/* Reliable version of signal(), using POSIX sigaction().  */
Sigfunc *
signal(int signo, Sigfunc *func)
{
	struct sigaction    act, oact;
	act.sa_handler = func;

	// must initialize the sa_mask member of the structure
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (signo == SIGALRM) {
#ifdef  SA_INTERRUPT
	    act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
		// intentionally set the SA_RESTART flag 
		// for all other than SIGALRM
	    act.sa_flags |= SA_RESTART;
	}
	if (sigaction(signo, &act, &oact) < 0)
	    return(SIG_ERR);
	return(oact.sa_handler);
}