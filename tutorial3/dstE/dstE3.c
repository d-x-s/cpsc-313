#include <stdio.h>
#include <stdint.h>

#include "dstE.h"

y86_register_t dstE(int cond, y86_icode_t icode, y86_register_t rB){
	if (icode == 0)
		return R_NONE;
	if (icode == 1)
		return R_NONE;
	if (icode == 2)
		if (cond)
			return rB;
		else
			return R_NONE;
	if (icode == 3)
		return rB;
	if (icode == 4)
		return R_NONE;
	if (icode == 5)
		return R_NONE;
	if (icode == 6)
		return rB;
	if (icode == 7)
		return R_NONE;
	if (icode == 8)
		return R_RSP;
	if (icode == 9)
		return R_RSP;
	if (icode == 10)
		return R_RSP;
	if (icode == 11)
		return R_RSP;
	if (icode == 14)
		return R_NONE;
	if (icode == 15)
		return R_NONE;
}
