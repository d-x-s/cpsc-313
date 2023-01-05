#include <stdio.h>
#include <stdint.h>

#include "dstE.h"

y86_register_t dstE(int cond, y86_icode_t icode, y86_register_t rB){
	if (icode == I_HALT)
		return R_NONE;
	if (icode == I_NOP)
		return R_NONE;
	if (icode == I_RRMVXX)
		if (cond)
			return rB;
		else
			return R_NONE;
	if (icode == I_IRMOVQ)
		return rB;
	if (icode == I_RMMOVQ)
		return R_NONE;
	if (icode == I_MRMOVQ)
		return R_NONE;
	if (icode == I_OPQ)
		return rB;
	if (icode == I_JXX)
		return R_NONE;
	if (icode == I_CALL)
		return R_RSP;
	if (icode == I_RET)
		return R_RSP;
	if (icode == I_PUSHQ)
		return R_RSP;
	if (icode == I_POPQ)
		return R_RSP;
	if (icode == I_INVALID)
		return R_NONE;
	if (icode == I_TOO_SHORT)
		return R_NONE;
}
