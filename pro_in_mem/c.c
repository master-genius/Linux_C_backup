#include <unistd.h>
#include <stdio.h>

char fuck_c[32] = "fuck";

int fc()
{
    read(0,fuck_c,31);
    printf("-->%s\n",fuck_c);
return 0;
}
