/*
 * myls.c
 * usage ./myls .
 * Objective - use this file as the basis for printing out various types of the
 * file. For example, whether it is a regular file or a directory file, etc. Hints are : <sys/stat.h> , struct stat sb, and stat() S_ISXXX();
 */

#include <sys/types.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;

	struct stat sb;

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL ){
		if (stat(dirp->d_name, &sb) < 0){
			fprintf(stderr, "Can't stat %s: %s\n", dirp->d_name,
							strerror(errno));
		}

		printf("%s\t", dirp->d_name);
		if(S_ISREG(sb.st_mode))
			printf("regular file\n");
		else if (S_ISDIR(sb.st_mode))
			printf("directory\n");
		else
			printf("unknown\n");
	}

	closedir(dp);
	return(0);
}
