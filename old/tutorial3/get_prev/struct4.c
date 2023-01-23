#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mystruct.h"

static struct mystruct *prev = NULL;
static int nleft = 0;

int get_prev(uint8_t *buf, size_t buflen, struct mystruct *ret) {
	if (buf != NULL) {
		nleft = buflen / sizeof(struct mystruct);
		prev = (struct mystruct *)(buf + buflen - sizeof(struct mystruct));
	}

	/* At this point, the buf == NULL case is identical to the buf != NULL case. */
	if (nleft == 0)
		return 1;
	memcpy(ret, prev, sizeof(struct mystruct));
	nleft--;
	prev--;
	return 0;
}
