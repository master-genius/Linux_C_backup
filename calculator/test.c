#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fdef.h"
#include "ddef.h"

#define OPERA       "+-*/"


int main(int ac, char* av[])
{
    if(ac<3)return 0;
    prec = PREC_DEF;
    int i, k;
    struct number a , b , c;

    int (*(f[4]))(struct number*,struct number*,struct number*);

    if(crnm(&a,av[1])==-1)return -1;
    if(crnm(&b,av[2])==-1)return -1;
    if(crnm(&zero,"0")==-1)return -1;
    //printf("  %d\n",a.bits);

    nm_out(&a);
    printf("\n");
    nm_out(&b);
    printf("\n");

    f[0] = bw_add;
    f[1] = bw_mis;
    f[2] = bw_mul;
    f[3] = bw_div;

    int err=0;

    for(i=0;i<4;i++)
    {
        err = (f[i])(&a,&b,&c);
        if(err==-1)
        {
            printf("error code:%d\n",err_num);
            goto end;
        }
        printf("%c ",OPERA[i]);
        nm_out(&c);printf("\n");
        nm_free(&c);
    }

end:
    nm_free(&a);
    nm_free(&b);
    //nm_free(&c);

return err;
}
