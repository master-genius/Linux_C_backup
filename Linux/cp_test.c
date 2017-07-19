#include	<unistd.h>
#include	<stdio.h>
#include	<fcntl.h>
#include	<sys/stat.h>

#define BUFF	4096

int main(int ac, char* av[])
{
	if(ac < 3)
	{
		printf("error:less arguments\n");
		return -1;
	}

	int fd=0;

	fd=open(av[1],O_RDONLY);
	if(fd<0)
	{
		perror("open:");
		return -1;
	}

	struct stat fst;

	if(stat(av[0],&fst)==-1)
	{
		perror("stat");
		return -1;
	}

	char buf[BUFF]={0,};

	//printf("%o\n",fst.st_mode);

	int fc=open(av[2],O_RDWR|O_CREAT,fst.st_mode);

	if(fc<0)
	{
		perror("open:");
		return -1;
	}

	int count=0;

	while((count=read(fd,buf,BUFF))>0)
		write(fc,buf,count);

	close(fd);
	close(fc);

return 0;
}
