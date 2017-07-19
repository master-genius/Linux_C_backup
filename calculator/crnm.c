#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ddef.h"
#include "fdef.h"

int crnm(struct number*n, char*ns)
{
    if(!n || !ns)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    int len = strlen(ns);
    if(len<=0)return -1;

    int start=0,end=0;
    int flag=0;

    if(ns[0]=='-')
    {n->pn_flag = '-';start=1;}
    else {start=0; n->pn_flag = '+';}

    int p=0;
    for(p=start;p<len;p++)
    {
        if(ns[p]=='.')break;
        if(flag==0 && ns[start]=='0')
            start++;
        else if(ns[start]> '0' && flag==0)
            flag=1;
    }

    n->ppl = p - start;

    end=len-1;
    while(end > p)
    {
        if(ns[end]> '0')break;
        end--;
    }

    if(end <= p)n->ppr = 0;
    else n->ppr = end - p;

    n->bits = n->ppl + n->ppr;

    if(n->bits <= 0)
        n->bits = 1;

    n->nm = (char*)malloc(sizeof(char)*(n->bits+1));
    if(!n->nm)
    {
        perror("malloc");
        return -1;
    }
    n->nm[0]=0;
    n->nm[n->bits] = END_CH;
//printf("bits=%d\n",n->bits);
    int i=0;
    while(start < p)
    {
        n->nm[i++] = ns[start]-48;
        start++;
    }

    int k = p+1;
//printf("k=%d\n",k);
    while(k <= end)
    {
        n->nm[i++] = ns[k]-48;
        k++;
    }

return 0;
}
