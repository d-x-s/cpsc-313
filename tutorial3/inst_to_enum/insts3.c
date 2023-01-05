#include <string.h>
#include "insts.h"

// Your function must be fewer than 20 lines of code (i.e., you cannot
// brute force the implementation). Our solution is 9 lines including
// everything below.

// If str is a valid instruction (as defined in insts.h), return
// the corresponding enum. If str is not a valid instruction,
// return I_INVALID.
inst_t inst_to_enum(const char *str) {
	/* Best not to hardcode the size of the table. */
	int nentries = sizeof(cmd_map) / sizeof(struct cmd_map_t);
	for (int i = 0; i < nentries; i++) {
		if (strcmp(str, cmd_map[i].cmd_str) == 0)
			return cmd_map[i].cmd;
	}
	return I_INVALID;
}
