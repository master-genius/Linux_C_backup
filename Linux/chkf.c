#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <asm-generic/errno-base.h>

int main(int ac, char* av[])
{

    for(int i=1;i<ac;i++)
    {
        if(access(av[i],F_OK)!=0)
        {
            if(errno==ENOENT)
                printf("%s is not here\n",av[i]);
            else
            {
                perror("access");
                return errno;
            }
        }
        else
            printf("%s is here\n",av[i]);
    }


return 0;
}
