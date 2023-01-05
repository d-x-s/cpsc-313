#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

/*
 * Build files to exhibit different characteristics:
 * Sparse: 1 GB file containing a character at offset 1 and offset 1GB+1
 * Medium: A file large enough to require an indirect block
 * Tiny: A 1-character file
 * Note: This program uses very crude error handling!
 */
int
main(int argc, char *argv[]) {
	char buf[4096];

	/* Create Medium file. */
	int fd = open("medium", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	assert(fd >= 0);
	for (int i = 0; i < 100; i++)
		assert(write(fd, buf, 4096) == 4096);
	assert(close(fd) == 0);

	/* Create sparse file. */
	fd = open("sparse", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	assert(fd >= 0);
	char c = 'a';
	assert(write(fd, &c, 1) == 1);
	assert(lseek(fd, 1024*1024*1024, SEEK_CUR) == 1024*1024*1024+1);
	assert(write(fd, &c, 1) == 1);
	assert(close(fd) == 0);

	/* Create tiny file. */
	fd = open("tiny", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	assert(fd >= 0);
	c = 'a';
	assert( write(fd, &c, 1) == 1);
	assert(close(fd) == 0);
}
