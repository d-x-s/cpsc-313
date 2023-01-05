/* Demonstrate using opendir/readdir to read a directory. */

#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	DIR *dirp;
	struct dirent *direntp;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./dirread <dir>\n");
		return 1;
	}

	dirp = opendir(argv[1]);
	if (dirp == NULL) {
		perror("dirread :");
		return 1;
	}

	while ((direntp = readdir(dirp)) != NULL)
		printf("Ino: %llu\tName: %s\n", direntp->d_ino, direntp->d_name);

	(void)closedir(dirp);

}
