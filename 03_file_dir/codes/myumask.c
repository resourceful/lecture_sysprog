#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int
main(void)
{
	umask(0);
	if (creat("foo", RWRWRW) < 0){
		fprintf(stderr, "Unable to create foo\n");
		exit(EXIT_FAILURE);
	}
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0){
		fprintf(stderr, "creat error for bar");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}


