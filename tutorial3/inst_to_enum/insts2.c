#include <string.h>
#include "insts.h"

// Your function must be fewer than 20 lines of code (i.e., you cannot
// brute force the implementation). Our solution is 9 lines including
// everything below.

// If str is a valid instruction (as defined in insts.h), return
// the corresponding enum. If str is not a valid instruction,
// return I_INVALID.
inst_t inst_to_enum(const char *str) {
	struct cmd_map_t *ptr;
	for (ptr = cmd_map; ptr < cmd_map + 30; ptr++)
		if (strcmp(ptr->cmd_str, str) == 0)
			return ptr->cmd;
	return I_INVALID;
}
