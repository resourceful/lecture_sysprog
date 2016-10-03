#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/syscall.h>


void withSync() {
	int idx = 0;
	int g = 0;
	int f[9];
	for(idx = 0; idx <= 9; idx++) {
		char filename[20];
		sprintf(filename, "f_%d.txt", idx);
		if(idx == 0) 
		{
			g = open(filename, O_RDWR | O_CREAT);
			lseek (g, 0, SEEK_END);
			int records = 1;
			int i = 0;
			char *buf = NULL;
			buf = (char*) malloc(1024 * 64);
			memset (buf, 0xcafe, 1024 * 64);
			for(i = 0; i < records; i++) {
				write(g, buf, 1 * 1024);
			}
		} else {
			f[idx] = open(filename, O_RDWR | O_CREAT);

			lseek (f[idx], 0, SEEK_END);

			int records = 1;
			int i = 0;
			char *buf = NULL;

			buf = (char*) malloc(1024 * 64);
			memset (buf, 0xcafe, 1024 * 64);

			for(i = 0; i < records; i++) {
				write(f[idx], buf, 1 * 1024);
			}
					usleep(1000);
			if(idx == 9) {fsync(f[idx]);}
			close (f[idx]);
		}
	}
	close(g);
}

int main(int argc, const char * argv[]) {
	withSync();
	return 0;
}

