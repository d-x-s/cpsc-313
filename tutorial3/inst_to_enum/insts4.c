#include <string.h>
#include "insts.h"

// Your function must be fewer than 20 lines of code (i.e., you cannot
// brute force the implementation). Our solution is 9 lines including
// everything below.

// If str is a valid instruction (as defined in insts.h), return
// the corresponding enum. If str is not a valid instruction,
// return I_INVALID.
inst_t inst_to_enum(const char *str) {
	/* This was easier to read when I had one test on each line, but that failed the autograder. */
        if (strcmp(str,  "nop") == 0) { return  I_NOP;} if (strcmp(str,  "halt") == 0) { return  I_HALT;} if (strcmp(str,  "rrmovq") == 0) { return  I_RRMOVQ;} if (strcmp(str,  "irmovq") == 0) { return  I_IRMOVQ;} if (strcmp(str,  "rmmovq") == 0) { return  I_RMMOVQ;} if (strcmp(str,  "mrmovq") == 0) { return  I_MRMOVQ;} if (strcmp(str,  "pushq") == 0) { return  I_PUSHQ;} if (strcmp(str,  "popq") == 0) { return  I_POPQ;} if (strcmp(str,  "call") == 0) { return  I_CALL;} if (strcmp(str,  "ret") == 0) { return  I_RET;} if (strcmp(str,  "j") == 0) { return  I_J;} if (strcmp(str,  "jeq") == 0) { return  I_JEQ;} if (strcmp(str,  "jne") == 0) { return  I_JNE;} if (strcmp(str,  "jl") == 0) { return  I_JL;} if (strcmp(str,  "jle") == 0) { return  I_JLE;} if (strcmp(str,  "jg") == 0) { return  I_JG;} if (strcmp(str,  "jge") == 0) { return  I_JGE;} if (strcmp(str,  "addq") == 0) { return  I_ADDQ;} if (strcmp(str,  "subq") == 0) { return  I_SUBQ;} if (strcmp(str,  "mulq") == 0) { return  I_MULQ;} if (strcmp(str,  "modq") == 0) { return  I_MODQ;} if (strcmp(str,  "divq") == 0) { return  I_DIVQ;} if (strcmp(str,  "andq") == 0) { return  I_ANDQ;} if (strcmp(str,  "xorq") == 0) { return  I_XORQ;} if (strcmp(str,  "cmoveq") == 0) { return  I_CMOVEQ;} if (strcmp(str,  "cmovne") == 0) { return  I_CMOVNE;} if (strcmp(str,  "cmovl") == 0) { return  I_CMOVL;} if (strcmp(str,  "cmovle") == 0) { return  I_CMOVLE;} if (strcmp(str,  "cmovg") == 0) { return  I_CMOVG;} if (strcmp(str,  "cmovge") == 0) { return  I_CMOVGE;}
	return I_INVALID;
}
