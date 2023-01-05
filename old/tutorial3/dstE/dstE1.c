#include <stdio.h>
#include <stdint.h>

#include "dstE.h"

y86_register_t dstE(int cond, y86_icode_t icode, y86_register_t rB){
    if (icode == I_OPQ || icode == I_IRMOVQ || (icode == I_RRMVXX && cond))
    {
        return rB;
    }
    else if (icode == I_PUSHQ || icode == I_POPQ || icode == I_CALL || icode == I_RET)
    {
        return R_RSP;
    }
    else
    {
        return R_NONE;
    }
}
