#include<stdio.h>

char*BitToRight(char*b , int n);

int main()
{
   char p[23]={0,};
   printf("Number..>");
   scanf("%s",p);
     int n;
    printf("Bit..>");
    scanf("%d" ,&n);
  BitToRight(p , n);
   printf("%s\n",p);
return 0;
}

char*BitToRight(char*b , int n)
{
   int i , j;
   if(n<=0)
      return b;
   for(i=0;b[i]!=0;i++)
      if(b[i]=='.')
      {
          if(b[i+n]==0)
          {
             for(j=n;b[i+j]==0;j--)
                 b[i+j]='0';
             for(j=0;j<n;j++)
                  b[j+i]=b[j+1+i];
             b[i+n]=0;
               return b;
          }
	  for(j=0;j<n;j++)
             b[i+j]=b[i+j+1];
          b[i+n]='.';
          return b;
      }
   if(b[i]==0)
      for(j=0;j<n;j++)
          b[i+j]='0';
return b;
}



