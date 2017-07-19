#include<stdio.h>

void exch_void(void*,void*,int size);

int main()
{
    printf("start:a=3,b=4\n");
    int a=3,b=4;
    exch_void(&a,&b,sizeof(int));
    printf("exchanged:a=%d,b=%d\n\n",a,b);
    printf("start:x=12.5,y=13.9\n");
    double x=12.5 ,y=13.9;
    exch_void(&x,&y,sizeof(double));
    printf("exchanged:x=%g,y=%g\n",x,y);
return 0;
}

void exch_void(void*a,void*b,int size)
{
     unsigned char tmp=0;
     unsigned char* p=NULL;
     unsigned char* q=NULL;
     p=(unsigned char*)a;
     q=(unsigned char*)b;
     for(int i=0;i<size;i++)
     {
         tmp=*(p+i);
         *(p+i)=*(q+i);
         *(q+i)=tmp;
     }
}
