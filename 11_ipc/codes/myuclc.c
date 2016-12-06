#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int
main(void)
{
	int		c;

	while ((c = getchar()) != EOF) {
		if (isupper(c))
			c = tolower(c);
		else if (islower(c))
			c = toupper(c);
		if (putchar(c) == EOF){
			fprintf(stderr, "output error");
			exit(1);
		}
		if (c == '\n')
			fflush(stdout);
	}
	exit(0);
}
