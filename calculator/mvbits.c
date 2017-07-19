#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

int mvbits(struct number*n, int bits)
{
    if(!n || !n->nm)
    {
        err_num = ERR_EMPT;
        return -1;
    }
    if(bits == 0)return 0;
    else if(bits > 0) goto move_to_right;
    else if(bits < 0) goto move_to_left;

move_to_left:;
    bits = -bits;
    if(bits <= n->ppl)
    {
        n->ppl -= bits;
        n->ppr += bits;
    }
    else if(bits > n->ppl)
    {
        add_buf = n->nm;
        n->nm = (char*)malloc(sizeof(char)*(n->bits + bits - n->ppl+1));
        if(!n->nm)
        {
            n->nm = add_buf;
            add_buf=NULL;
            perror("malloc");
            return -1;
        }
        n->end = n->bits + bits - n->ppl+1;
        int i,p,bm;
        bm = bits - n->ppl;
        for(p=0;p<bm;p++)
            n->nm[p]=0;
        for(i=0;i < n->bits && add_buf[i]!=END_CH;i++)
            n->nm[p++] = add_buf[i];
        n->nm[p]=END_CH;
        n->bits += bits - n->ppl;
        n->ppl = 0;
        n->ppr = n->bits;
        free(add_buf);
        add_buf=NULL;
    }
    return 0;

move_to_right:;
    if(bits <= n->ppr)
    {
        n->ppl += bits;
        n->ppr -= bits;
    }
    else if(bits > n->ppr)
    {
        int j,k;
        add_buf = n->nm;
        n->nm = (char*)malloc(sizeof(char)*(bits - n->ppr + n->bits+1));
        if(!n->nm)
        {
            n->nm = add_buf;
            add_buf = NULL;
            perror("malloc");
            return -1;
        }
        n->end = bits - n->ppr + n->bits+1;
        int bm = bits - n->ppr;
        for(j=0;j<n->bits;j++)
            n->nm[j] = add_buf[j];
        for(k=0;k<bm;k++)
            n->nm[j+k] = 0;
        n->bits += bits - n->ppr;
        n->nm[n->bits] = END_CH;
        n->ppl = n->bits;
        n->ppr = 0;
        free(add_buf);
        add_buf = NULL;
    }

return 0;
}
