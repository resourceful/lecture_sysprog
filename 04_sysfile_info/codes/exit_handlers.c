/* At least 32 exit handlers are pushed onto a stack and they are execute in
 * reverse order.
 */

#include <stdio.h>
#include <stdlib.h>

int cnt;

void
my_exit1(void) {
	printf("first exit handler: %d\n", cnt);
	cnt++;
}

void my_exit2(void) {
	printf("second exit handler: %d\n", cnt);
}


int
main(int argc, char **argv) {
	cnt = 0;
	if (atexit(my_exit2) != 0) {
		perror("can't register my_exit2\n");
		exit(1);
	}

	if (atexit(my_exit1) != 0) {
		perror("can't register my_exit1");
		exit(1);
	}

	if (atexit(my_exit1) != 0) {
		perror("can't register my_exit1");
		exit(1);
	}

	printf("End of main\n");

	return(0);
}
