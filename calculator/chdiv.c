#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

int chdiv(struct number*a, struct number*b, struct number*c)
{
    if(!a || !a->nm || !b || !b->nm || !c)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    struct number* p = &nm_buf_a;
    struct number* q = &nm_buf_b;
    struct number*r = &nm_buf_c;
    int npc = prec;

    int i;
    int mb= bitsm(a,b);
//printf("bits minus: %d\n",mb);
    if(err_num > 0)return -1;

    npc += mb;

    if(npc < 0)
    {
        return crnm(c,"0");
    }
    c->ppl = c->ppr = c->bits = 0;

    if(nm_copy(b,q)==-1)return -1;
    if(nm_copy(a,p)==-1)return -1;

    if(mvbits(q,mb)==-1)
        return -1;


    div_buf = (char*)malloc(sizeof(char)*(npc+2+prec));
    if(!div_buf)
    {
        nm_free(p);
        nm_free(q);
        perror("malloc");
        return -1;
    }

    int flag=0;
    int ret=0;
    int x=0,end=0;
    struct number* buf=NULL;
    for(x=0;x<npc+2+prec;x++)div_buf[x]=0;
    if(mb<0)x = -mb;
    else x=0;

    while(npc >= 0)
    {
        //nm_out(p);printf("  ");nm_out(q);printf("\n");
        ret=nm_comp(p,q);
        if(ret ==-1)
        {
            nm_free(p);
            nm_free(q);
            free(add_buf);
            return -1;
        }
        else if(ret == MORE)
        {
            if(flag==0 && npc >= prec){flag=1;mb++;npc++;}
            div_buf[x]++;
            ret = chmis(p,q,r);
            if(ret==-1)
            {
                nm_free(p);
                nm_free(q);
                free(div_buf);
                return -1;
            }
            nm_free(p);
            buf = p;
            p = r;
            r = buf;

        }
        else if(ret==EQUAL)
        {
            if(flag==0 && npc >= prec){mb++;flag=1;npc++;}
            div_buf[x]++;
            break;
        }
        else if(ret == LESS)
        {
            npc--;
            if(npc < 0)break;
            x++;
            div_buf[x]=0;
            if(mvbits(p,1)==-1)
            {
                free(div_buf);
                nm_free(p);
                nm_free(q);
                return -1;
            }
        }
        if(flag==0)flag=1;
    }
    nm_free(p);
    nm_free(q);
    end = x;
    //for(i=0;i<=x;i++)printf("%d",div_buf[i]);printf("\n");
    i=0;
    //x=0;
    if(mb >= 0)
    {
        x=0;
        for(x=0;x<end;x++)
            if(div_buf[x]>0)break;
        c->ppl = mb;
        if((end-x+1) < mb){end = mb +x-1; c->ppr=0;}
        else c->ppr = end - x + 1 - mb;
    }
    else
    {
        x = -mb;
        c->ppr = end-x+1-mb-1;
        x = x+mb+1;
        c->ppl = 0;
    }
    c->bits = c->ppl+c->ppr;
//    printf("mb=%d end=%d c->ppl=%d c->ppr=%d c->bits=%d\n",mb,end,c->ppl,c->ppr,c->bits);
    c->end = c->bits+1;
    c->nm = (char*)malloc(sizeof(char)*(c->end));
    if(!c->nm)
    {
        free(div_buf);
        div_buf=NULL;
        return -1;
    }
    c->nm[c->bits]=END_CH;

    while(x<=end)
    {
        c->nm[i] = div_buf[x];
        i++;x++;
    }
    free(div_buf);
    div_buf=NULL;

return 0;
}
