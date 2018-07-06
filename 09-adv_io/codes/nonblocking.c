#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

char	buf[500000];



/* flags are the file status flags to turn off */
void
clr_fl(int fd, int flags)
{
	int		val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0){
		fprintf(stderr, "fcntl F_GETFL error");
		exit(1);
	}

	val &= ~flags;		/* turn flags off */

	if (fcntl(fd, F_SETFL, val) < 0){
		fprintf(stderr, "fcntl F_SETFL error");
		exit(1);
	}
}

/* flags are file status flags to turn on */
void
set_fl(int fd, int flags) 
{
	int		val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0){
		fprintf(stderr, "fcntl F_GETFL error");
		exit(1);
	}

	val |= flags;		/* turn on flags */

	if (fcntl(fd, F_SETFL, val) < 0){
		fprintf(stderr, "fcntl F_SETFL error");
		exit(1);
	}
}

int
main(void)
{
	int	 ntowrite, nwrite;
	char	*ptr;
	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);

	set_fl(STDOUT_FILENO, O_NONBLOCK);  /* set nonblocking */

	ptr = buf;

	while (ntowrite > 0) {
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	clr_fl(STDOUT_FILENO, O_NONBLOCK);  /* clear nonblocking */

	exit(0); 
}