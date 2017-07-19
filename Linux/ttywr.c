#include<stdio.h>

int main()
{
   char ins[256]={0,};
   printf("enter your instrn_>");
   fgets(ins,256,stdin);
   FILE*fd=NULL;
   fd=fopen("/dev/tty","w");
   if(fd==NULL)
     {
        perror("fopen");
        return 1;
     }
   fprintf(fd,"%s",ins);
   fflush(fd);

   fclose(fd);

return 0;
}
