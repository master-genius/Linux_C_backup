#include	<stdio.h>
#include	"scan.h"
#include	"set_tty.h"
#include	"read_def.h"
#include	"set_tty.h"

int main(int ac,char*av[])
{
   if(ac==1)
   {
       printf("Error:less file name\n");
       fflush(stdout);
       return 1;
   }
   else
   {
      if(set_in_mode(START_MODE))
        return 1;
      printf("\x1b[2J\x1b[;H");
      fflush(stdout);
      scan_file(av[1]);
   }
return set_in_mode(END_MODE);
}
