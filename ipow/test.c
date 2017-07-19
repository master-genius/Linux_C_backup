#include <stdio.h>
#include <stdlib.h>
#include "fdef.h"
#include "ddef.h"

#define COMP    ">=<"

int main(int ac, char* av[])
{
    if(ac<3)return 0;

    prec = PREC_DEF;

    int i, k;
    struct number a , b , c;

    if(crnm(&a,av[1])==-1)return -1;
    if(crnm(&b,av[2])==-1)return -1;
  //  if(crnm(&zero,"0")==-1)return -1;

    int err = bw_ipow(&a,&b,&c);
    if(err == -1)return -1;

    nm_out(&a);
    printf("  ");

    nm_out(&b);
    printf("  ");

    nm_out(&c);
    printf("\n");

    nm_free(&a);
    nm_free(&b);
    nm_free(&c);

return 0;
}
