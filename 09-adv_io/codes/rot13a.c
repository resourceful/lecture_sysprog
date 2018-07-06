#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

#define BSZ 4096
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

unsigned char buf[BSZ];

unsigned char
translate(unsigned char c)
{
	if (isalpha(c)) {
		if (c >= 'n')
			c -= 13;
		else if (c >= 'a')
			c += 13;
		else if (c >= 'N')
			c -= 13;
		else
			c += 13;
	}
	return(c);
}

int
main(int argc, char* argv[])
{
	int	ifd, ofd, i, n, nw;

	if (argc != 3){
		fprintf(stderr, "usage: rot13 infile outfile");
		exit(1);
	}
	if ((ifd = open(argv[1], O_RDONLY)) < 0){
		fprintf(stderr, "can't open %s", argv[1]);
		exit(1);
	}
	if ((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0){
		fprintf(stderr, "can't create %s", argv[2]);
		exit(1);
	}

	while ((n = read(ifd, buf, BSZ)) > 0) {
		for (i = 0; i < n; i++)
			buf[i] = translate(buf[i]);
		if ((nw = write(ofd, buf, n)) != n) {
			if (nw < 0){
				fprintf(stderr, "write failed");
				exit(1);
			}
			else {
				fprintf(stderr, "short write (%d/%d)", nw, n);
				exit(1);
			}
		}
	}

	fsync(ofd);
	exit(0);
}
