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

int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL )
		printf("%s\t", dirp->d_name);

	closedir(dp);
	return(0);
}
