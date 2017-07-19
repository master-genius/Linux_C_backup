#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ddef.h"
#include "fdef.h"

int bw_add(struct number*a, struct number*b, struct number*c)
{
    if(!a || !a->nm || !b || !b->nm || !c)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    if(a->pn_flag == '+' && b->pn_flag == '+')
    {
        c->pn_flag = '+';
        return chadd(a,b,c);
    }
    else if(a->pn_flag == '-' && b->pn_flag == '+')
    {
        return chmis(b,a,c);
    }
    else if(a->pn_flag == '+' && b->pn_flag == '-')
    {
        return chmis(a,b,c);
    }
    else if(a->pn_flag == '-' && b->pn_flag == '-')
    {
        c->pn_flag = '-';
        return chadd(a,b,c);
    }

return ERR_UNPN;
}
