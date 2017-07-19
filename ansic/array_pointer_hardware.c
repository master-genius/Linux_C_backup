#include<stdio.h>

int main()
{
  char a[10];
  printf("%p\n%p\n%p\n%p\n",&a,&a+1,a+9,*(&a+1));
return 0;
}
