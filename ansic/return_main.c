#include<stdio.h>

static int i=0;

int main()
{
   printf("BruceWang!\n");
   i++;
   if(i<9)
     return main();
return 0;
}
