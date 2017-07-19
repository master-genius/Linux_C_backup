#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

int main(int ac, char*av[])
{
   if(ac==1)
     return 1;
   DIR*dir=opendir(av[1]);
   DIR*dirc=NULL;
   if(dir!=NULL)
   {
      chdir(av[1]);
      dirc=opendir("test");
      if(dirc==NULL)
        printf("error:%d\n",errno);
      else
        closedir(dirc);
      closedir(dir);
   }
   else
      printf("Error;%d\n",errno);
return 0;
}