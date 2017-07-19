#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

long long prim(int);

int main(int ac, char* av[])
{
    if(ac<2)
    {
        time_t tm;
        tm = time(0);
        srand((int)tm);
        int x = rand()%129+1;
        int e;
        e = prim(x);
        if(e== -1)
            printf("Null\n");
        else printf("%d\n",e);
    }
    else if(ac > 2)
    {
        int n = 0;
        n = atoi(av[2]);
        if(strcmp("-n",av[1])==0)
        {
            int b;
            for(b=1;b<=n;b++)
                printf("%lld%c",prim(b),(b%13)?' ':'\n');
            if(n%13)printf("\n");
        }
        else if(strcmp("-e",av[1])==0)
        {
            printf("%lld\n",prim(atoi(av[2])));
        }
    }
    else
    {
        printf("less number\n");
        return -1;
    }

return 0;
}

long long prim(int n)
{
    if(n<1)return -1;
    else if(n==1)return 2;

    long long i, m, k, e, j;
    for(i=3,k=2;k<n;)
    {
        st: i+=2;
        m = (long long)pow((double)(i),(double)(0.5));
        for(j=2; j<= m; j++)
        {
            if((i%j)==0)
            {
                //i+=2;
                goto st;
            }
        }
        if(j>m)
            k++;
    }
return i;
}
