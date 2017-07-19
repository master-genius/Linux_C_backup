#include<stdio.h>
#include<stdlib.h>

void exch1(char*,char*);
void exch2(char*,char*);
void exch3(char*,char*);

int main()
{
   char a[5]={0,};
   void (*fun[3])(char*,char*);
   fun[0]=exch1;
   fun[1]=exch2;
   fun[2]=exch3;
start:printf("Get data_>");
     fgets(a,5,stdin);
     if(a[0]==27)
       goto end;
     if(a[0]==9 && a[1]=='c')
     {
        system("clear");
        goto start;
     }
     if(a[2]<48||a[2]>'3')
     {
          printf("arguments error\n");
          goto start;
     }
     else
     {
       fun[(a[2]-48)-1](a,a+1);
       printf("exchanged:%c %c\n",a[0],a[1]);
       goto start;
     }

end:return 0;
}

void exch1(char*a,char*b)
{
   *a=*a-*b;
   *b=*b+*a;
   *a=*b-*a;
}

void exch2(char*a,char*b)
{
   char tmp=0;
   tmp=*a;
   *a=*b;
   *b=tmp;
}

void exch3(char*a,char*b)
{
   *a^=*b^=*a^=*b;
}
