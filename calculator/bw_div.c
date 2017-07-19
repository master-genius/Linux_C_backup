#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

int bw_div(struct number*a, struct number*b, struct number*c)
{
    if(!a || !a->nm || !b || !b->nm || !c)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    if(prec< PREC_MIN || prec > PREC_MAX)
        prec = PREC_DEF;

    int ret=nm_comp(b,&zero);
    if(ret==-1)return -1;
    else if(ret== EQUAL)
    {
        err_num = ERR_DIVZ;
        return -1;
    }
    ret = nm_comp(a,&zero);
    if(ret==-1)return -1;
    else if(ret == EQUAL)
        return crnm(c,"0");

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

return chdiv(a,b,c);
}
