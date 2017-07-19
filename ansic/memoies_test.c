#include<stdio.h>

struct data
{
   char d_c;
   int ik;
};

int cpmem(void*,void*,int,int);

int main()
{
   struct data m1,m2;
  printf("get char and number_>");
  scanf("%c%d",&m1.d_c,&m1.ik);
  if(cpmem(&m1,&m2,sizeof(m1),sizeof(m2))==0)
     printf("%c %d\n",m2.d_c,m2.ik);

return 0;
}

int cpmem(void*mf,void*mt,int fsize, int tsize)
{
   if(fsize<=0 || tsize<=0)
   {
      printf("arguments error\n");
      return -1;
   }
   if(fsize>tsize)
   {
      printf("too small space to recieve data\n");
      return -2;
   }
    char *f=NULL,*t=NULL;
   for(int i=0;i<fsize;i++)
   {
      f=(char*)(mf)+i;
      t=(char*)(mt)+i;
      *t=*f;
   }
return 0;
}
