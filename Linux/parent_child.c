#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
//#include<stdlib.h>

#define MG_MAX 256

int clr_mbuf(char*,int);

void sign(int sig);

int main()
{
    int p[2],fd[2];
    if(pipe(p) || pipe(fd))
    {
        perror("pipe");
        return -1;
    }

    char message[MG_MAX]={0,};
    char msg[MG_MAX]={0,};
    int status=0;
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
        signal(SIGINT,sign);
        signal(SIGQUIT,sign);
        int count=0;
        while(1)
        {
            write(1,"parent_>",8);
            if((count=read(0,message,MG_MAX))==-1)
            {
                perror("read");
                kill(cpid,SIGKILL);
                break;
            }
            else
            if(count==0)
            {
                write(p[1],"nothing\n",8);
            }
            if(write(p[1],message,strlen(message))==-1)
            {
                perror("write");
                kill(cpid,SIGKILL);
                break;
            }
            
            if(write(1,"wait child..\n",13)==-1)
                perror("write");
            clr_mbuf(message,MG_MAX);
            clr_mbuf(msg,MG_MAX);
            if(read(fd[0],msg,256)==-1)
            {
                perror("read");
                kill(cpid,SIGKILL);
                break;
            }
            if(strcmp(msg,"cquit")==0)
                break;
            else
            if(strcmp(msg,"ok")!=0)
            {
                printf("child error\n");
                kill(cpid,SIGKILL);
                break;
            }
        }
        if(close(p[1]) || close(fd[0]))
           perror("close");
        printf("waiting child exit..\n");
        fflush(stdout);
        if(wait(&status)!=cpid)
            perror("wait");
        printf("child exit:%d\n",status);
        printf("Now parent exit..\n");
    }

    if(cpid==0)
    {
        signal(SIGINT,SIG_IGN);
        signal(SIGQUIT,SIG_IGN);
        int nm=0;
        if(close(p[1])!=0 || close(fd[0])!=0)
            perror("close");
        while(1)
        {
            if((nm=read(p[0],message,256))==-1)
            {
                perror("read");
                kill(getppid(),SIGKILL);
                break;
            }
            else
            if(nm==0)
                write(1,"error:\n",7);
            if(write(1,"child recieve:",14)==-1)
                perror("write");
            if(write(1,message,strlen(message))==-1)
            {
                perror("write");
                kill(getppid(),SIGKILL);
                break;
            }
            if(strcmp(message,"quit")==0 || strcmp(message,"quit\n")==0)
            {
                if(write(fd[1],"cquit",5)==-1)
                {
                    perror("write");
                    kill(getppid(),SIGKILL);
                    break;
                }
                break;
            }
            else
            if(strcmp(message,"clr\n")==0 || strcmp(message,"clr")==0\
                || strcmp(message,"CLR\n")==0 || strcmp(message,"CLR")==0)
            {
                printf("\x1b[2J\x1b[;H");
                fflush(stdout);
            }
            clr_mbuf(message,256);
            if(write(fd[1],"ok",2)==-1)
                perror("write");
        }

        if(close(p[0]) || close(fd[1]))
            perror("close");
        printf("Now child exit..\n");
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

void sign(int sig)
{
    printf("enter 'quit' to exit\n");
}
