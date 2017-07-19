#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>

struct termios tty_mode;
int fflg;

//int set_mode(int flag, int fd);

int main()
{
    int p[2];
    if(pipe(p))
    {
        perror("pipe");
        return -1;
    }
    char pcmd=0;
    char ccmd=0;
    char message[256]={0,};
    int cpid=fork();
    if(cpid<0)
    {
       perror("fork");
       return -1;
    }
    if(cpid>0)
    {
        if(close(p[0])!=0)
	   perror("close");
	printf("parent running\n");
	printf("parent_>");
	fflush(stdout);
	read(0,message,256);
	write(p[1],"r",1);
	write(p[1],message,strlen(message));
	if(close(p[1]))
	   perror("close");
	printf("waiting child exit..\n");
	fflush(stdout);
	wait(NULL);
        printf("parent exit..\n");
    }
    if(cpid==0)
    {
       char cmd=0;
       while(cmd!='r')
           read(p[0],&cmd,1);
       if(close(p[1]))
         perror("close");
       printf("child running\n");
       read(p[0],&message,256);
       printf("child recieve message:%s\n",message);
       fflush(stdout);
       quit:if(close(p[0]))
         perror("close");
       printf("child exit..\n");
       fflush(stdout);
       sleep(1);
    }

return 0;
}
/*
int set_mode(int flag , int fd)
{
   int fg=0;
   if(fd<0)return -1;
   if(flag==1)
   {
      if(tcgetattr(fd,&tty_mode)==-1)return -1;
      tty_mode.c_lflag &= ~ICANON;
      fflg=fg=fcntl(fd,F_GETFL);
      if(fg==-1)
        return -1;
      fg|=O_NONBLOCK;
      if(fcntl(fd,F_SETFL,fg)==-1)
        return -1;
      return tcsetattr(fd,TCSANOW,&tty_mode);
   }
   else
   if(flag==0)
   {
      tty_mode.c_lflag|=ICANON;
      if(tcsetattr(fd,TCSANOW,&tty_mode))
        return -1;
      if(fcntl(fd,F_SETFL,fflg)==-1)
        return -1;
   }
   else
      return -1;
return 0;
}
*/
