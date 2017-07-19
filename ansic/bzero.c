#include<stdio.h>

void* bzero(void*,int size);

struct btest
{
   int xb;
   double db;
   char cb;
};

int main()
{
   int x=9;
   bzero(&x, sizeof(x));
   struct btest ts;
   ts.xb=3;
   ts.db=8.5;
   ts.cb='q';
   bzero(&ts,sizeof(ts));
   printf("%d %d %g %d\n",x,ts.xb,ts.db,ts.cb);
   printf("bit:\n");
   for(int i=0;i<31;i++)
       printf("%d ",(x&(1<<i)) >>i);
   printf("\n");

return 0;
}

void*bzero(void*v,int size)
{
   if(v==NULL || size<=0)
	return NULL;
   char* buf=NULL;
   char* q=(char*)v;
   for(int i=0;i<size;i++)
   {
      buf=q+i;
      *buf=0;
   }

return v;
}
