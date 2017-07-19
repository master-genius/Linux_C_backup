#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fdef.h"
#include "ddef.h"

int chadd(struct number*a, struct number*b, struct number*c)
{
    int maxb = (a->ppl > b->ppl)? a->ppl : b->ppl;
    maxb += (a->ppr > b->ppr)? a->ppr : b->ppr;

    int bit_to_this=0;

    int bit=0, bm=0, p=0;

    add_buf = (char*)malloc(sizeof(char)*(maxb+2));
    if(!add_buf)
    {
        perror("malloc");
        return -1;
    }

    int abs = a->bits-1;
    int bbs = b->bits-1;

    //printf("%d %d\n%d  %d\n",a->ppr , b->ppr, a->bits,b->bits);

    if(a->ppr > b->ppr)
    {
        bm = a->ppr - b->ppr;
        while(bm>0)
        {
            add_buf[p] = a->nm[abs];
            p++;
            abs--;
            bm--;
        }
    }
    else if(a->ppr < b->ppr)
    {
        bm = b->ppr - a->ppr;
        while(bm > 0)
        {
            add_buf[p]=b->nm[bbs];
            p++;
            bbs--;
            bm--;
        }
    }

    while(abs>=0 && bbs>=0)
    {
        bit = a->nm[abs] + b->nm[bbs] + bit_to_this;
        bit_to_this = bit/10;
        bit -= bit_to_this*10;
        add_buf[p] = bit;
        p++;
        abs--;
        bbs--;
    }

    if(abs >= 0)
    {
        while(abs>=0)
        {
            bit = a->nm[abs]+bit_to_this;
            bit_to_this = bit/10;
            bit -= bit_to_this*10;
            add_buf[p] = bit;
            p++;
            abs--;
        }
    }
    else if(bbs>=0)
    {
        while(bbs>=0)
        {
            bit = b->nm[bbs]+bit_to_this;
            bit_to_this = bit/10;
            bit -= bit_to_this*10;
            add_buf[p] = bit;
            p++;
            bbs--;
        }
    }

    c->ppl = (a->ppl > b->ppl)?a->ppl:b->ppl;

    if(bit_to_this > 0)
    {
        add_buf[p++]=bit_to_this;
        c->ppl++;
    }

    c->ppr = (a->ppr > b->ppr)?a->ppr:b->ppr;
    int start=0;
    while(c->ppr > 0)
    {
        if(add_buf[start]==0)
        {
            c->ppr--;
            start++;
        }
        else break;
    }
    c->bits = p-start;

    c->nm = (char*)malloc(sizeof(char)*(c->bits+1));
    if(!c->nm)
    {
        perror("malloc");
        goto end;
    }

    p--;
    bit=0;
    while(p >= start)
    {
        c->nm[bit]=add_buf[p];
        p--;
        bit++;
    }
    c->nm[c->bits]=END_CH;

    end:
    free(add_buf);
    add_buf=NULL;
return 0;
}
