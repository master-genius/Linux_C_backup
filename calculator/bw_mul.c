#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

int bw_mul(struct number*a, struct number*b, struct number*c)
{
    if(!a || !a->nm || !b || !b->nm || !c)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    if(a->pn_flag=='-')
        c->pn_flag='-';
    else if(a->pn_flag=='+')
        c->pn_flag='+';
    else return ERR_UNPN;

    if(b->pn_flag=='-')
    {
        if(c->pn_flag=='-')
            c->pn_flag = '+';
        else
            c->pn_flag = '-';
    }
    else if(b->pn_flag=='+')
        ;
    else return ERR_UNPN;

return chmul(a,b,c);
}
