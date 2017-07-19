#include	"set_tty.h"
#include	"read_def.h"
#include	<termios.h>
#include	<stdio.h>

int set_in_mode(int flag)
{
   if(flag==START_MODE)
   {
        if(tcgetattr(0,&stty)==-1)
        {
          printf("error to get tty setting\n");
          return -1;
        }
        stty.c_lflag&=~ICANON;
		stty.c_lflag&=~ECHO;
        if(tcsetattr(0,TCSANOW,&stty)==-1)
        {
            printf("error to set new tty\n");
            return -1;
        }
   }
   if(flag==END_MODE)
   {
       stty.c_lflag|=ICANON;
       stty.c_lflag|=ECHO;
       if(tcsetattr(0,TCSANOW,&stty)==-1)
       {
           printf("error reset default tty setting\n");
           fflush(stdout);
           return -1;
       }
   }
return 0;
}
