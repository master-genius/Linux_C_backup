#include <stdio.h>
#include <stdlib.h>

long long mf(long long , long long);

int main(int ac, char* av[])
{
    if(ac<3)return -1;

    int a,b;

    a = atoll(av[1]);
    b = atoll(av[2]);

    printf("maximum common factor:%d\n",mf(a,b));

return 0;
}

long long mf(long long a, long long b)
{
    
    return (b==0)?(-1):((a%b)?(mf(b,a%b)):b);
}
