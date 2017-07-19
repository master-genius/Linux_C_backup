#include<stdio.h>

#define fbuf(c) while((c=getchar())!='\n')

int main()
{
   printf("Continue?[y/n]");
   char c=0,b=0;
   c=getchar();
   fbuf(b);
   b=0;
   if(c=='y'||c=='Y')
     return main();
   else
   if(c=='N'||c=='n')
     return 0;
   else
      return main();
return 0;
}
