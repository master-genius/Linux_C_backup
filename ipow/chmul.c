#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"
#include <time.h>

int chmul(struct number*a,struct number*b, struct number*c)
{
    if(!a || !b || !c || !a->nm || !b->nm)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    c->nm = (char*)malloc(sizeof(char)*2);
    if(!c->nm)
    {
        perror("malloc");
        return -1;
    }
    c->bits = c->ppl = 1;
    c->ppr = 0;
    c->end = 2;
    c->nm[0] = 0;
    c->nm[1] = END_CH;

    int mb = b->bits-1;

    struct number* p = &nm_buf_a;
    struct number* q = &nm_buf_b;

    int t=0,bit=0;
    int bit_to_this=0;

    mul_buf = NULL;
    mul_buf = (char*)malloc(sizeof(char)*(a->bits+2));
    if(!mul_buf)
    {
        perror("malloc");
        return -1;
    }

    int i,err=0,j,st;
    int mvbs=0;
    //clock_t start = 0, end = 0;
    for(i=0; i< b->bits;i++)
    {
        if(b->nm[i]==0)
        {
            mb--;
            continue;
        }
        if((err=nm_cut(c,q))==-1)break;

        {
            t=0;
            for(j=a->bits-1;j >= 0;j--)
            {
                if(a->nm[j]==0 || b->nm[i]==0)
                {
                    bit = bit_to_this;
                    mul_buf[t++] = bit;
                    bit_to_this = 0;
                }
                else
                {
                    bit = ntable[ a->nm[j]-1 ][ b->nm[i]-1 ] + bit_to_this;
                    if(bit>9)
                    {
                        bit_to_this = bit/10;
                        bit -= bit_to_this*10;
                    }
                    else
                        bit_to_this = 0;
                    mul_buf[t++] = bit;
                }
            }
            if(bit_to_this > 0)
                mul_buf[t++] = bit_to_this;

            st=0;
            p->ppr = a->ppr;
            while(p->ppr > 0)
            {
                if(mul_buf[st] > 0)break;
                else st++;
                p->ppr--;
            }
            p->ppl = t - st + mb - p->ppr;
            if(mb > p->ppr)
            {
                mvbs = mb - p->ppr;
                p->ppr = 0;
            }
            else
            {
                mvbs = 0;
                p->ppr -= mb;
            }

            p->nm = (char*)malloc(sizeof(char)*(t-st+1+mvbs));
            if(!p->nm)
            {
                err=-1;
                perror("malloc");
                break;
            }

            p->bits = t-st+mvbs;
            p->end = t-st+mvbs+1;
            for(j=0,t--;t>=st;j++,t--)
                p->nm[j] = mul_buf[t];
            for(t=0;t<mvbs;t++)
                p->nm[j++] = 0;
            p->nm[p->bits]=END_CH;
            t = st  = j = 0;
            bit_to_this = 0;
        }
        mb--;
        if((err=chadd(p,q,c))==-1)break;
        nm_free(q);
    }
    free(mul_buf);
    mul_buf = NULL;
    if(p && p->nm)nm_free(p);
    if(q && q->nm)nm_free(q);

    if(err==0)
    {
        err = mvbits(c,-b->ppr);
        if(err==-1)nm_free(c);
    }

return err;
}
