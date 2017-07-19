#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    int fd=open("dup",O_RDONLY|O_CREAT,S_IRWXU);
    if(fd<0)
    {
       perror("open");
       return -1;
    }
    if(dup2(fd,STDIN_FILENO)!=STDIN_FILENO)
    {
        perror("dup2");
	return -1;
    }
    char message[256]={0,};
    while(1)
    {
       read(fd,message,256);
       write(1,message,strlen(message));
       if(message[strlen(message)-1]=='\n')
          message[strlen(message)-1]=0;
       if(!strcmp(message,"quit"))break;
    }
return 0;
}