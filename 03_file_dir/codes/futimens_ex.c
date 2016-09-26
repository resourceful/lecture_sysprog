/* 
 * code is broken
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	int             i, fd;
	struct stat     statbuf;
	struct timespec time[2];

	for (i = 1; i < argc; i++) {
		if (stat(argv[i], &statbuf) < 0) {	/* fetch current times */
			fprintf(stderr, "%s: stat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* truncate */
			fprintf(stderr, "%s: open error", argv[i]);
			continue;
		}
		time[0].tv_sec = statbuf.st_atime;
		time[1].tv_sec = statbuf.st_mtime;
#ifdef __APPLE__
		/* futimens and utimensat doesnot work in some osx */
		/* update to current time */
		if (futimes( fd, &ubuf.modtime) < 0) 
#else
		if (futimens(fd, time) < 0)		/* reset times */
#endif
			fprintf(stderr, "%s: futimens error", argv[i]);
		close(fd);
	}
	exit(0);
}
