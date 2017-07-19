#include<stdio.h>
#include<unistd.h>

char*num_to_char(int,char*);
int change_dir();
int main(int ac, char*av[])
{
   char name[256]={0,},pname[256]={0,};
   int pid=0;
   FILE*fd=NULL;
   if(change_dir()!=0)
      return -1;
   if(ac==1)
   {
      pid=getpid();
      num_to_char(pid,name);
      if(chdir(name)==-1)
      {
            printf("fail:Can not get this program's name");
            return 2;
      }
      else
      {
          fd=fopen("status","r");
          if(fd!=NULL)
	  {
             fgets(pname,256,fd);
	     printf("%s",pname);
	     fflush(stdout);
	  }
          else
          {
             perror("fopen");
             return -2;
          }
      }
   }
   for(int i=1;i<ac;i++)
   {
      if(chdir(av[i])==-1)
         printf("error:maybe %s is not exist\n",av[i]);
      else
      {
         fd=fopen("status","r");
         if(fd!=NULL)
	 {
             fgets(pname,256,fd);
	     printf("%s",pname);
	     fflush(stdout);
	     fclose(fd);
	 }
         else
             perror("fopen");
      }
      if(change_dir()!=0)
        return -1;
   }
return 0;
}

int change_dir()
{
   if(chdir("/proc/")==-1)
   {
         printf("!Error to open proc\n");
	 perror("fopen");
         return -1;
   }
return 0;
}

char*num_to_char(int numb, char*name)
{
    int i;
    for(i=0;name[i]!=0;i++)
         name[i]=0;
    i=0;
    for(;numb!=0;numb/=10)
    {
        name[i++]=(numb%10)+48;
    }
    int k=0;
    for(;k<i/2;k++)
    {
        name[k]=name[k]-name[i-1-k];
        name[i-1-k]=name[i-1-k]+name[k];
        name[k]=name[i-1-k]-name[k];
    }
return name;
}
