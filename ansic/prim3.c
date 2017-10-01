#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

long long prim(int);

int primn(int*, int*);

int primy(int*, int* );

#define YDONE   -2
#define NONE    -3

#define DEFV    129

#define NMAX    1<<30

#define BEGIN   0
#define END     1
#define CNUM    2
#define TNUM    3
#define JNUM    4
#define NUMF    5
#define NUMT    6
#define NUMC    7
#define ARGS    8

#define NLINE   10

struct agsl
{
    int index[ARGS];
    int num[ARGS];
};

void get_help();

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
    else if(ac >= 2)
    {
        for(i=1; i<ac; i++)
        {
            if (strcmp("-h",av[i])==0)
            {
                get_help();
                return 0;
            }
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
            else if(strcmp("-j",av[i])==0)
            {
                i++;
                as.index[TNUM] = i;
            }
            else if(strcmp("-n",av[i])==0)
            {
                i++;
                as.index[CNUM] = i;
            }
            else if(strcmp("-b",av[i])==0)
            {
                i++;
                as.index[NUMF] = i;
            }
            else if(strcmp("-e",av[i])==0)
            {
                i++;
                as.index[NUMT] = i;
            }
            else if(strcmp("-c",av[i])==0)
            {
                i++;
                as.index[NUMC] = i;
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

    int flag = 0;

    if(as.num[NUMT]>0)
    {
        again:;
        int ret=0, count=1;
        int backup = as.num[NUMF];
        int bn = as.num[NUMT] - as.num[NUMF]+1;
        while(ret!=YDONE)
        {
            ret = primn(&(as.num[NUMF]), &(as.num[NUMT]));
            if(ret==-1) return -1;
            else if(ret>0)
            {
                printf("%d%c",ret,(count%NLINE)?' ':'\n');
                count++;
            }
        }
        if(count>1 && ((count-1)%NLINE))
            printf("\n");
        printf("counts:%d\n",count-1);
        if(flag)goto end;
    }

    if(as.num[NUMC]>0 && flag==0)
    {
        as.num[NUMF] = 2;
        as.num[NUMT] = as.num[NUMC];
        flag = 1;
        goto again;
    }

end:
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

int primn(int* fn, int* tn)
{
    if((!fn || !tn) || *tn<=1)return -1;
    if((*fn)<=1)*fn=2;

    if(*fn > *tn)return YDONE;

    int i, k, m, flag=0;

    for(;*fn<=*tn;(*fn)++)
    {
        k = (long long)pow((double)(*fn),0.5);
        for(m=2; m<=k;m++)
        {
            if(((*fn)%m)==0)
                break;
        }
        if(m>k){m = *fn; flag=1;(*fn)++;break;}
    }

return (flag)?m:NONE;
}

void get_help()
{
    printf("output prim number\n");
    printf("    -f[num] -t[num]: from the numberth to another numberth\n");
    printf("    -b[num] -e[num]: start at a number end at a number\n");
    printf("    -n [num]: the first num count of prim number\n");
    printf("    -c [num]: it also be -b 0 -e num\n");

}

// From this function, I understand the yeild key in Python.
