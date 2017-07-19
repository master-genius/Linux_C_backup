#include<stdio.h>

struct add
{
   int it;
   int *at;
};

int main()
{
  struct add p;
  int *q=&p.it;
  p.it=1;
  p.at=q;
  p.at[1]=2;
  p.at[0]=9;
return 0;
}
