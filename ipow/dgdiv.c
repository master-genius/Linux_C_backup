#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

int dgdiv(struct number* a, int* b, int* m)
{
    if(!a || !a->nm || !b || !m)
    {
        err_num = ERR_EMPT;
        return -1;
    }

    if(a->ppl > POW_MBS)
    {
        err_num = ERR_OPOW;
        return -1;
    }

    int num=0;
    int to=10;

    int i;
    for(i=0;i< a->ppl;i++)
    {
        num *= 10;
        num += a->nm[i];
    }
  //  printf("%d ",num);
    *b = *m = 0;

    while(num >= 2)
    {
        if(num&1)
            *b |= 1<<(*m);
        (*m)++;
        num /= 2;
    }

//    printf("%d %d\n",*b,*m);

return 0;
}
