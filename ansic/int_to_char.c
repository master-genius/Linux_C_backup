#include<stdio.h>

#define fbuf(c) while((c=getchar())!='\n')

char*nuttch(int,char*);

int main()
{
  int n=0;
  char name[12]={0,},c=0;
inn:printf("get a number_>");
    if(scanf("%d",&n)==0)
    {
       printf("input error\n");
       fbuf(c);
       goto inn;
    }
    printf("%s\n",(nuttch(n,name)==NULL)?"NULL":name);
return 0;
}

char*nuttch(int numb, char*name)
{
    if(numb==0)
    {
       printf("0 is NULL\n");
       return NULL;
    }
    if(numb<0)
    {
       name[0]='-';
       nuttch(-numb,name+1);
    }
    else
    {
        int i;
        for(i=0;name[i]!=0;i++)
            name[i]=0;
	for(;numb!=0;numb/=10)
           name[i++]=(numb%10)+48;
        for(int k=0;k<i/2;k++)
        {
           name[k]=name[k]-name[i-1-k];
           name[i-1-k]=name[i-1-k]+name[k];
           name[k]=name[i-1-k]-name[k];
        }
    }
return name;
}
