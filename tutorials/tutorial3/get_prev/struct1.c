#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mystruct.h"

static struct mystruct *prev = NULL;
static int nleft = 0;

int get_prev(uint8_t *buf, size_t buflen, struct mystruct *ret) {
	if (buf != NULL) {
		/* Figure out how many structures we can fit in the buffer. */
		size_t tmpsize = buflen;
		for (nleft = 0; tmpsize >= sizeof(struct mystruct); nleft++) {
			tmpsize -= sizeof(struct mystruct);
		}

		if (nleft <= 0)
			return 1;
		prev = (struct mystruct *)(buf + (buflen - (nleft * sizeof(struct mystruct))));
		memcpy(ret, (uint8_t *)prev + (nleft - 1) * sizeof(struct mystruct), sizeof(struct mystruct));
		nleft--;
		return 0;
	}
	if (buf == NULL) {
		if (nleft == 0)
			return 1;
		memcpy(ret, (uint8_t *)prev + (nleft - 1) * sizeof(struct mystruct), sizeof(struct mystruct));
		nleft--;
		return 0;
	}
	return 1;
}
