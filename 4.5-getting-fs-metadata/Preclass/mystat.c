#include <stdio.h>
#include <sys/stat.h>

/*
 * Call stat on argv[1];
 */
int main(int argc, char *argv[]) {
	struct stat statbuf;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./mystat <file>\n");
		return 1;
	}

	stat(argv[1], &statbuf);
	printf("File size: %lld\n", statbuf.st_size);
	printf("Block count: %lld\n", statbuf.st_blocks);
	printf("Block size: %d\n", statbuf.st_blksize);
}
