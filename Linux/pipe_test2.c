#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define MESSAGE "get message from pipe[0]\n"

int main()
{
   int p[2];
   if(pipe(p))
   {
      perror("pipe");
      return -1;
   }
   if(write(p[1],MESSAGE,strlen(MESSAGE))<0)
   {
      perror("write");
      return -1;
   }
    char ms[256]={0,};
   if(read(p[0],ms,256)<0)
   {
      perror("read");
      return -1;
   }
   if(write(1,ms,strlen(ms))<0)
   {
      perror("write");
      return -1;
   }
   if(close(p[0]))
      perror("close");
   if(close(p[1]))
      perror("close");
return 0;
}
