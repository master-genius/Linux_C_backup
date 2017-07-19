#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

long long prim(int);

#define DEFV    129

#define NMAX    10010011

#define BEGIN   0
#define END     1
#define CNUM    2
#define TNUM    3
#define ARGS    4

#define NLINE   11

struct agsl
{
    int index[ARGS];
    int num[ARGS];
};

int main(int ac, char* av[])
{
    struct agsl as;
    int i;

    for(i=0;i<ARGS;i++)
    {
        as.index[i]=0;
        as.num[i]=-1;
    }

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
        for(i=1; i<ac; i++)
        {
            if(strcmp("-f",av[i])==0)
            {
                i++;
                as.index[BEGIN] = i;
            }
            else if(strcmp("-t",av[i])==0)
            {
                i++;
                as.index[END] = i;
            }
            else if(strcmp("-e",av[i])==0)
            {
                i++;
                as.index[TNUM] = i;
            }
            else if(strcmp("-n",av[i])==0)
            {
                i++;
                as.index[CNUM] = i;
            }
            else
            {
                printf("unknow argument\n");
                return -1;
            }
        }
    }

    for(i=0;i<ARGS;i++)
    {
        if(as.index[i]<ac)
            {
                as.num[i] = atoi(av[as.index[i]]);
                if(as.num[i] > NMAX)
                {
                    printf("error: too long number\n");
                    return -1;
                }
            }
        else
        {
            printf("less argument\n");
            return -1;
        }
    }

    if(as.num[BEGIN]>0 && as.num[END]>0)
    {
        printf("from %d to %d\n",as.num[BEGIN],as.num[END]);
        for(i=as.num[BEGIN];i<=as.num[END];i++)
            printf("%lld%c",prim(i),(i>0 && (i-as.num[BEGIN]+1)%NLINE==0)?'\n':' ');
        if((as.num[END]-as.num[BEGIN]+1)%NLINE)
            printf("\n");
    }

    if(as.num[CNUM]>0)
    {
        printf("from 0 to %d\n",as.num[CNUM]);
        for(i=1;i<=as.num[CNUM];i++)
            printf("%lld%c",prim(i),(i>0 && (i%NLINE==0))?'\n':' ');
        if((as.num[CNUM]%NLINE))
            printf("\n");
    }

    if(as.num[TNUM]>0)
        printf("%lld\n",prim(as.num[TNUM]));

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
