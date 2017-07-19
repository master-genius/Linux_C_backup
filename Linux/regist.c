#include<stdio.h>
#include<string.h>
#include<pwd.h>
#include<unistd.h>
#include<error.h>

#define INF_MAX 512

int srh_reg(char*);
int create_envirt();
int out_all();

int main(int ac,char*av[])
{
    int er=create_envirt();
    if(er!=0)
      return 1;
      if(ac==1)
      {
          if(out_all()==-1)
	  {
             printf("can't output data\n");
             return 2;
	  }
	  return 0;
      }
      if(strcmp("-edit",av[1])==0)
      {
         execl("/usr/bin/nano","nano ","reginf",NULL);
         return 0;
      }
    int si=1;
    er=srh_reg(av[1]);
    if(er!=0)
      printf("There is no data which you need to search in the file\n");
return 0;
}

int srh_reg(char*key)
{
     FILE*fd=fopen("reginf","r");
     if(fd==NULL)
     {
         printf("Don't find the data\n");
         perror("fopen");
         return -1;
     }
     char buf[INF_MAX]={0,};
     int flg=0;
     while(!feof(fd))
     {
         fgets(buf,INF_MAX,fd);
         if(strstr(buf,key)!=NULL)
         {
            flg=1;
            break;
         }

     }
     fclose(fd);
     if(flg==1)
     {
         printf("%s",buf);
         return 0;
     }

return -2;
}

int out_all()
{
   FILE*fd=fopen("reginf","r");
   if(fd==NULL)
   {
      perror("fopen");
      return -1;
   }
   char inf[INF_MAX]={0,};
   while(!feof(fd))
   {
      fgets(inf,INF_MAX,fd);
      printf("%s",inf);
      fflush(stdout);
   }
   fclose(fd);
return 0;
}

int create_envirt()
{
    struct passwd*pw=getpwuid(getuid());
    if(pw==NULL)
      return 1;
    if(chdir(pw->pw_dir)==-1)
    {
        printf("can't change workspace to '%s'\n",pw->pw_dir);
        return 2;
    }
    if(chdir("app/register")==-1)
    {
        printf("can't change workspace to 'register'\n");
        return 3;
    }
return 0;
}
