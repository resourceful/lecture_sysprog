
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
	int		fd;

	if ((fd = creat("file.hole", S_IRUSR | S_IWUSR )) < 0)
		perror("creat error");

	if (write(fd, buf1, 10) != strlen(buf1))
		perror("buf1 write error");
	/* offset now = 10 */

	if (lseek(fd, 16384, SEEK_SET) == -1)
		perror("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != strlen(buf2))
		perror("buf2 write error");
	/* offset now = 16394 */

	exit(0);
}