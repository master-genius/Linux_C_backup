#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"
#include <time.h>

int bw_ipow(struct number*a, struct number*b, struct number*c)
{
    if(!a || !b || !c || !a->nm || !b->nm)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    int ret = 0, d,m;
    ret = dgdiv(b,&d,&m);
    if(ret==-1)return -1;

    struct number bufa, bufb;

    struct number* p = &bufa;
    struct number* q = &bufb;

    if(m == 0)
    {
        if(a->ppl>0 && a->nm[0]==1)
            return nm_copy(a,c);
        else if(a->ppl == 0)
            return crnm(c,"1");
    }

    ret = nm_copy(a,p);
    if(ret==-1)return -1;

    clock_t start = 0 , end = 0;

    while(m>0)
    {
        m--;
        ret = chmul(p,p,q);
        if(ret == -1)
        {
            nm_free(p);
            return -1;
        }
        nm_free(p);
        nm_cut(q,p);
        if((1<<m)&d)
        {
            ret = chmul(p,a,q);
            if(ret == -1)
            {
                nm_free(p);
                return -1;
            }
            nm_free(p);
            nm_cut(q,p);
        }
    }

    nm_cut(p,c);

return 0;
}
