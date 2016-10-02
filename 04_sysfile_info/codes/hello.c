/* 
 * compile with following line
 * cc -nostartfiles -o hello hello.c -e _my_main
 * this example serves two purposes. 
 * First, it shows that main() is nothing but an term to start the code which
 * is used by C Library. main() is linked with _start() fuction in GNU C
 * library in linking process. 
 * Second, press ^C after hello, world is on the screen, and examine the exit
 * status with $? 
 * Is it different from normal exit?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_main()
{
	printf("hello, world\n");
	sleep(5);
	return 0;
}

void _start()
{
	int ret = my_main();
	exit(ret);
}

