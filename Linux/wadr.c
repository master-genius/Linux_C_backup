#include "webaddr.h"
#include <stdio.h>
#include <string.h>

#define WEBBUF	4096

int main(int ac, char* av[])
{
	char web[WEBBUF]={0,};
	strcpy(web,WEBAD);
	int len=strlen(web);
	for(int i=0;i<len;i++)if(web[i]=='*')web[i]='\n';

	if(ac<2)
	{
		printf("%s\n",web);
	}
	else
	if(!strcmp(av[1],"-tf"))
	{
		if(ac<3)
		{
			printf("error:less the file name\n");
			fflush(stdout);
			return -1;
		}
		FILE*fd=fopen(av[2],"w+");
		if(!fd)
		{
			perror("fopen:");
			return -1;
		}
		if(fwrite(web,sizeof(char),len,fd)<=0)
		{
			perror("fwrite:");
			fclose(fd);
			return -1;
		}
		fclose(fd);
	}
	else
	{
		printf("error:undefine command string\n");
		fflush(stdout);
		return -1;
	}
	
return 0;
}