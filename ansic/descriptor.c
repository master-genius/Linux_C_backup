#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

void des(int n);

int main()
{
   des(13);
return 0;
}

void des(int n)
{
   int *fd=(int*)malloc(n*sizeof(int));
   if(fd==NULL)
     return ;
   char name[9]={"Bruce"};
   for(int i=0;i<n;i++)
   {
       fd[i]=open(name,O_RDWR|O_CREAT,S_IRWXU);
       if(fd[i]>0)
         printf("descriptor:%d\n",fd[i]);
   }
   for(int i=0;i<n;i++)
      if(fd[i]>0)
        close(fd[i]);
   sleep(2);
   remove(name);
}
