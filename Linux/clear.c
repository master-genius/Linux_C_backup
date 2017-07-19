#include<stdio.h>

int main()
{
   printf("\x1b[2J\x1b[;H");
   fflush(stdout);
return 0;
}
