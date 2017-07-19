#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>

#define MG_MAX 256

int clr_mbuf(char*,int);

int main()
{
    int p[2],fd[2];
    if(pipe(p)||pipe(fd))
    {
        perror("pipe");
        return -1;
    }

    char message[MG_MAX]={0,};
    char msg[MG_MAX]={0,};
    int cpid=fork();
    if(cpid<0)
    {
       perror("fork");
       return -1;
    }
    if(cpid>0)
    {
        if(close(p[0])!=0 || close(fd[1])!=0)
	   perror("close");
	printf("parent running\n");
	fflush(stdout);
	while(1)
	{
		write(1,"parent_>",8);
		read(0,message,MG_MAX);
		write(p[1],message,strlen(message));
		write(1,"wait child..\n",13);
		clr_mbuf(message,MG_MAX);
		clr_mbuf(msg,MG_MAX);
		read(fd[0],msg,256);
		if(strcmp(msg,"cquit")==0)
			break;
	}
	if(close(p[1]) || close(fd[0]))
	   perror("close");
	printf("waiting child exit..\n");
	fflush(stdout);
	wait(NULL);
        printf("parent exit..\n");
    }
    if(cpid==0)
    {
	if(close(p[1])!=0 || close(fd[0])!=0)
		perror("close");
        while(1)
	{
           read(p[0],message,256);
	   write(1,"child recieve:",14);
	   write(1,message,strlen(message));
	   if(strcmp(message,"quit")==0 || strcmp(message,"quit\n")==0)
	   {
		write(fd[1],"cquit",5);
		break;
	   }
	   clr_mbuf(message,256);
	   write(fd[1],"ok",5);
	}

       if(close(p[0]) || close(fd[1]))
         perror("close");
       printf("child exit..\n");
       fflush(stdout);
       usleep(300000);
    }

return 0;
}

int clr_mbuf(char*msg,int mmax)
{
	if(msg==NULL || mmax<=0)
		return -1;
   for(int i=0;i<mmax && msg[i]!=0;i++)
   {
	msg[i]=0;
	if(i==mmax && msg[i]!=0)
		msg[i]=0;
   }

return 0;
}
