#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

int bit_mul(struct number*a, char bit, struct number*b)
{
    if(!a || !a->nm || !b)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    mul_buf = (char*)malloc(sizeof(char)*(a->bits+2));
    if(!mul_buf);

return 0;
}
