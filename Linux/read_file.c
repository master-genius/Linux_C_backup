#include<unistd.h>
#include<stdio.h>
#include<termios.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<string.h>

#define LINE_MAX	23
#define CHAR_MAX	512
#define START_MODE	0
#define END_MODE	1
#define WAIT		"---MORE[%2.1f%%]---"

struct termios stty;

int set_in_mode(int);
int get_size(char*);
int scan_file(char*,int);

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
      int f_size=0;
      f_size=get_size(av[1]);
      scan_file(av[1],f_size);
   }
return set_in_mode(END_MODE);
}

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

int get_size(char*path)
{
     struct stat fstat;
     if(stat(path,&fstat))
       return -1;
return (int)fstat.st_size;
}

int scan_file(char*path,int f_size)
{
    FILE*fd=fopen(path,"r");
    if(fd==NULL)
    {
       perror("fopen");
       return -1;
    }
    char cmd=0;
    int line=1,count=0;
    int d=0;
    char l[CHAR_MAX]={0,};
    for(int i=0;i<LINE_MAX && !feof(fd);i++,line++)
    {
        fgets(l,CHAR_MAX,fd);
        count+=strlen(l);
        printf("%d: %s",line,l);
        fflush(stdout);
    }
    d=printf(WAIT,((1.0*count)/f_size)*100);
    while(!feof(fd))
    {
	cmd=getchar();
	if(cmd=='\n')
	{
        fgets(l,CHAR_MAX,fd);
	    count+=strlen(l);
	    printf("\x1b[1K\x1b[%dD",d);
            printf("%d: %s",line,l);
	    d=printf(WAIT,((1.0*count)/f_size)*100);
            fflush(stdout);
	    line++;
	    cmd=0;
	}
	else
	if(cmd==' ')
	{
	    printf("\x1b[1K\x1b[%dD",d);
	    for(int i=0;i<LINE_MAX && !feof(fd);i++,line++)
	    {
	        fgets(l,CHAR_MAX,fd);
            count+=strlen(l);
            printf("%d: %s",line,l);
            fflush(stdout);
	    }
	    cmd=0;
	    d=printf(WAIT,((1.0*count)/f_size)*100);
 	}
        else
        if(cmd=='q'|| cmd=='Q')
           break;
    }
    fclose(fd);
    printf("\x1b[1K\x1b[%dD",d);
return 0;
}
