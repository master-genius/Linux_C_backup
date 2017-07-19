#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int rand_num(int,int);

int main()
{
   int jd=0,er=0;
   for(int i=0;i<300000;i++)
   {
      jd=rand_num(24,1);
      if(jd>=24||jd<=0)
        er++;
   }
   printf("find error:%d\n",er);
return 0;
}

int rand_num(int mx,int sd)
{
    srand((int)time(0)+sd);
return ((rand()%mx)<=0)?1:(rand()%mx);
}