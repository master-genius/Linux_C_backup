#include<stdio.h>
#include<setjmp.h>
#include<string.h>

jmp_buf start;

int get_passwd(char*);

int main()
{
   char pswd[32]={0,};
   if(setjmp(start))
      printf("passwd error\n");
   if(get_passwd(pswd)==-1)
      longjmp(start,1);
return 0;
}

int get_passwd(char*pswd)
{
    printf("enter passwd_>");
    fgets(pswd,32,stdin);
    for(int i=0;pswd[i]!=0;i++)
       if(pswd[i]=='\n')
         pswd[i]=0;
    if(!strcmp(pswd,"fuck"))
      return 0;
    else
      return -1;
}
