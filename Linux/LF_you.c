#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<curses.h>
#include<sys/wait.h>

int main()
{
   char name[256]={0,};
   printf("Enter your name_>");
   fgets(name,256,stdin);
   initscr();
   clear();
   refresh();
   int cpid=fork();
   if(cpid==0)
   {
       int flag=0;
       for(int i=0;i<30;i++)
       {
           printf("%d s\n",30-i);
           fflush(stdout);
           move(i+1,(flag==0)?3:49);
           (flag==0)?addstr("I Love You"):addstr("Fuck You");
           flag^=1;
           refresh();
           sleep(1);
           clear();
           refresh();
       }endwin();
   }
   else
   if(cpid>0)
   {
       int status=0;
       if(wait(&status)!=cpid)
       {
          printf("Child program error to quit\n");
       }
        printf("status:%d\n",status);
   }
   else
      printf("error fork\n");
endwin();
return 0;
}
