#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// adopted from figure 2.17 in the text
#ifdef  OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif
// If OPEN_MAX is indeterminate, this might be inadequate.
#define OPEN_MAX_GUESS  256
long open_max(void)
{
    if (openmax == 0) {
        errno = 0;
    /* first time through */
        if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
            if (errno == 0)
                openmax = OPEN_MAX_GUESS;   /* it is indeterminate */
            else
                fprintf(stderr, "sysconf error for _SC_OPEN_MAX");
        }
    }
    return(openmax);
}

int main(){
   printf("The number of file decriptors a process can open: %d\n", (int)RLIMIT_NOFILE);
   printf("The number of file decriptors an user can open: %ld\n", openmax );
   return 0;
}
