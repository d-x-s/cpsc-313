#include <string.h>
#include "insts.h"

// Your function must be fewer than 20 lines of code (i.e., you cannot
// brute force the implementation). Our solution is 9 lines including
// everything below.

// If str is a valid instruction (as defined in insts.h), return
// the corresponding enum. If str is not a valid instruction,
// return I_INVALID.
inst_t inst_to_enum(const char *str) {
	for (int i = 0; i < 30; i++) {
		int len1 = strlen(str);
		int len2 = strlen(cmd_map[i].cmd_str);
		int maxlen = len1 > len2 ? len1 : len2;
		if (memcmp(str, cmd_map[i].cmd_str, maxlen + 1) == 0)
			return cmd_map[i].cmd;
	}
	return I_INVALID;
}
