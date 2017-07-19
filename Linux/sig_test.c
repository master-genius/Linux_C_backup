#include<stdio.h>
#include<termios.h>
#include<signal.h>

void fint(int );

int main()
{
   char flag=0;
   struct termios orig;
   if(tcgetattr(0,&orig)==-1)
   {
      printf("get tty setting to fail\n");
      return -1;
   }
   orig.c_lflag&=~ICANON;
   //orig.c_lflag&=~ECHO;
   if(tcsetattr(0,TCSANOW,&orig)==-1)
   {
       printf("error:setting tty\n");
       return -2;
   }
   signal(SIGINT,fint);
   signal(SIGQUIT,fint);
   while(1)
  {
       printf("enter 'q' to quit_>>");
       fflush(stdout);
       flag=getchar();
       if(flag=='q'||flag=='Q')
         break;
       printf("\x1b[2J\x1b[;H");
  }
  printf("\x1b[2J\x1b[;H");
   orig.c_lflag|=ICANON;
   //orig.c_lflag|=ECHO;
   if(tcsetattr(0,TCSANOW,&orig)==-1)
   {
      printf("It is so fucking:set tty\n");
      return -3;
   }

return 0;
}

void fint(int sig)
{
    printf("\n%s can't exit\n",(sig==SIGINT)?"ctrl-c":((sig==SIGQUIT)?"ctrl-\\":"null"));
}
