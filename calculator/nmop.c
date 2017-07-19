#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"


int nm_copy(struct number*a, struct number*b)
{
    if(!a || !a->nm || !b)
    {
        err_num = ERR_EMPT;
        return -1;
    }
    b->nm = (char*)malloc(sizeof(char)*(a->bits+1));
    if(!b->nm)
    {
        perror("malloc");
        return -1;
    }
    b->ppl = a->ppl;
    b->ppr = a->ppr;
    b->bits = a->bits;
    b->end = b->bits+1;

    int i;
    for(i=0;i< b->bits && a->nm[i]!=END_CH;i++)
    {
        b->nm[i] = a->nm[i];
    }
    b->nm[b->bits]=END_CH;

return 0;
}

int nm_cut(struct number*a, struct number*b)
{
    if(!a || !a->nm || !b)
    {
        err_num = ERR_EMPT;
        return -1;
    }
    b->ppl = a->ppl;
    b->ppr = a->ppr;
    b->bits = a->bits;
    b->end = a->end;
    b->nm = a->nm;
    a->nm=NULL;
    a->ppl = a->ppr = a->bits = a->end = 0;

return 0;
}

int nm_comp(struct number*a, struct number*b)
{
    if(!a || !b || !a->nm || !b->nm)
    {
        err_num = ERR_EMPT;
        return -1;
    }
    int ast=0, bst=0;
    int aend=0, bend=0;

    for(ast=0;ast < a->ppl; ast++)
        if(a->nm[ast]>0)break;
    for(aend=a->bits-1;aend >= a->ppl;aend--)
        if(a->nm[aend]>0)break;

    for(bst=0;bst < b->ppl; bst++)
        if(b->nm[bst]>0)break;
    for(bend=b->bits-1;bend >= b->ppl;bend--)
        if(b->nm[bend]>0)break;
//printf("ast=%d;bst=%d;aend=%d;bend=%d a->ppl=%d b->ppl=%d\n",ast,bst,aend,bend,a->ppl,b->ppl);
    if((a->ppl-ast) > (b->ppl-bst))
        return MORE;
    else if((a->ppl-ast) < (b->ppl-bst))
        return LESS;
    else
    {
        while((ast <= aend) && (bst <= bend))
        {
            if(a->nm[ast] > b->nm[bst])return MORE;
            else if(a->nm[ast] < b->nm[bst])return LESS;
            ast++;
            bst++;
        }
        if(ast <= aend)return MORE;
        else if(bst <= bend)return LESS;
        //return EQUAL;
    }

return EQUAL;
}

int nm_free(struct number*a)
{
    if(!a)return -1;

    if(a->nm)free(a->nm);
    a->nm=NULL;
    a->ppl = a->ppr = a->bits = a->end = 0;

return 0;
}

int nm_out(struct number*n)
{
    if(!n || !n->nm)
    {
        err_num = ERR_EMPT;
        return -1;
    }
    int k;
    if(n->pn_flag == '-')
        printf("%c",n->pn_flag);

    if(n->ppl==0 && n->ppr>0)printf("0");

    for(k=0;k < n->bits && n->nm[k]!=END_CH;k++)
    {
        if((k==(n->ppl))&& n->ppr>0)printf(".");
        printf("%d",n->nm[k]);
    }
    //printf("\n");
return 0;
}

int bitsm(struct number*a, struct number*b)
{
    if(!a || !a->nm || !b || !b->nm)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    int ast=0,bst=0;
    for(ast=0;ast < a->ppl;ast++)
        if(a->nm[ast]>0)break;

    for(bst=0;bst < b->ppl; bst++)
        if(b->nm[bst]>0)break;

    int ab = a->ppl - ast;
    int bb = b->ppl - bst;
    int mb = 0;

    if(ab >0 && bb > 0)
    {
        return (ab-bb);
    }
    else if(ab > 0 && bb <= 0)
    {
        mb = ab;
        for(bst = 0; bst < b->ppr; bst++)
            if(b->nm[bst+b->ppl]==0)mb++;
            else break;
        return mb;
    }
    else if(ab <= 0 && bb >0)
    {
        mb = -bb;
        for(ast=0;ast < a->ppr;ast++)
            if(a->nm[ast+a->ppl]==0)
                mb--;
            else break;
        return mb;
    }
    else if(ab<=0 && bb<=0)
    {
        mb = 0;
        for(ast = 0; ast < a->ppr; ast++)
            if(a->nm[ast+a->ppl]==0)mb--;
            else break;
        for(bst=0; bst < b->ppr; bst++)
            if(b->nm[bst+b->ppl]==0)mb++;
            else break;
        return mb;
    }

return 0;
}

