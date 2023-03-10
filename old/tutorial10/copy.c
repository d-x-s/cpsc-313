#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/**
 * copy content from infile to outfile
 * 1. return 1 if success, and 0 otherwise
 * 2. infile should never be modified
 * 3. outfile should not be created if infile does not exist
 */
int copy(const char *infile, const char *outfile) {

    int ret = 0;

    int in = open(infile, O_RDONLY, 0);
    if (in < 0) {
	fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    int out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out < 0) {
	fprintf(stderr, "%s\n", strerror(errno));
    	(void)close(in);
        return -1;
    }

    char buffer[4096];
    ssize_t bytes;

    while ((bytes = read(in, buffer, sizeof(buffer))) > 0) {
        ssize_t wbytes = write(out, buffer, bytes);
	if (wbytes != bytes) {
		fprintf(stderr, "%s\n", strerror(errno));
		ret = -1;
		break;
	}
    }

    (void)close(in);
    (void)close(out);
    return ret;
}

int
main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: ./copy infile outfile\n");
		return 1;
	}
	return copy(argv[1], argv[2]);
}
