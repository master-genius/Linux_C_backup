#include<stdio.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define MODE_BLK 1
#define MODE_LOVE 2
#define MODE_FUCK 3

#define SHOW_MOV 16
#define SHOW_FLASH 32
#define SHOW_MVFLH 64

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define DELAY 25600
#define QUIT 'q'

#define X_MAX 80
#define Y_MAX 24
#define X_MIN 3
#define Y_MIN 1
/*
int left;
int right;
int start;
int end;
*/
int x;
int y;
int ch_max;

struct light
{
   char line[256];
   struct light*next;
};
typedef struct light* light_t;

void clr();
int light_mode(light_t light,int mode);
int light_show(light_t light,int show);
int light_read(light_t light,FILE*fd);
int light_move(char* mv);
void show_scrn(light_t light);
int light_flash(light_t light,int*n);
int set_in_mode(int flag);
light_t light_initial(light_t light);
void light_destroy(light_t light);

int main()
{
    light_t light=NULL;
    light=light_initial(light);
    if(light==NULL)
      return -1;
    int option=0;
    printf("1:block 2:love 3:fuck _>");
    scanf("%d",&option);
    if(option<=0||option>3)
      option=MODE_FUCK;
    if(light_mode(light,option)==-1)
      return -1;
    printf("take a type of show[16:move 32:flash 64:flash&move]_>");
    scanf("%d",&option);
    if(set_in_mode(1)==-1)
      return -1;
    if(light_show(light,option)==-1)
      return -1;
    light_destroy(light);
    if(set_in_mode(0)==-1)
      return -1;
return 0;
}

light_t light_initial(light_t light)
{
   light=(light_t)malloc(sizeof(struct light));
   if(light==NULL)
   {
      perror("malloc");
      return NULL;
   }
return light;
}

void light_destroy(light_t light)
{
    light_t p=NULL;
    while(light)
    {
       p=light->next;
       free(light);
       light=p;
    }
}

void clr()
{
   printf("\x1b[2J\x1b[;H");
   fflush(stdout);
}

int light_mode(light_t light,int mode)
{
   FILE*fd=NULL;
   if(!light)
     return -1;
   if(mode==MODE_BLK)
      goto block;
   if(mode==MODE_LOVE)
      goto love;
   if(mode==MODE_FUCK)
      goto fuck;

   printf("error:unknow mode\n");
   fflush(stdout);
   return -1;
block:fd=fopen("block","r");
      if(!fd)
      {
         perror("fopen");
         return -1;
      }
      if(light_read(light,fd)==-1)
      {
         printf("Error:light_read\n");
	 return -1;
      }
      return 0;

love:fd=fopen("love","r");
     if(!fd)
     {
        perror("fopen");
        return -1;
     }
     if(light_read(light,fd)==-1)
     {
         printf("Error:light_read\n");
	 return -1;
     }
     return 0;

fuck:fd=fopen("fuck","r");
     if(!fd)
     {
        perror("fopen");
        return -1;
     }
     if(light_read(light,fd)==-1)
     {
         printf("Error:light_read");
	 return -1;
     }
     return 0;

return 0;
}

int light_show(light_t light,int show)
{
   char cmd=RIGHT,cbuf=0;
   if(!light)
     return -1;
   if(show==SHOW_MOV)
      goto move;
   if(show==SHOW_FLASH)
      goto flash;
   if(show==SHOW_MVFLH)
      goto flash_move;
   printf("error:unknow type of show");
   return -1;

move:x=13;y=13;
     while(cmd!=QUIT)
     {
        cbuf=getchar();
        if(cbuf==UP||cbuf==DOWN||cbuf==LEFT||cbuf==RIGHT||cbuf==QUIT)
           cmd=cbuf;
        light_move(&cmd);
        show_scrn(light);
        usleep(DELAY);
        clr();
     }
     return 0;
flash:x=24;y=13;
      int rd=0;
      while(cmd!=QUIT)
      {
          cmd=getchar();
          if(light_flash(light,&rd)==-1)
	    return -1;
          show_scrn(light);
	  usleep(DELAY);
	  clr();
      }
      return 0;

flash_move:x=13;y=13;
          int n=0;
          while(cmd!='q')
          {
              cbuf=getchar();
              if(cbuf==UP||cbuf==DOWN||cbuf==LEFT||cbuf==RIGHT||cbuf==QUIT)
                 cmd=cbuf;
              light_move(&cmd);
              light_flash(light,&n);
              show_scrn(light);
              usleep(DELAY);
              clr();
          }
          return 0;
return 0;
}

int light_move(char*mv)
{
    if(*mv==UP)
       goto up;
    if(*mv==DOWN)
       goto down;
    if(*mv==LEFT)
       goto left;
    if(*mv==RIGHT)
       goto right;
    return 0;
up:if(y>Y_MIN)
      y-=1;
   else
      *mv=RIGHT;
   return 0;
down:if(y<Y_MAX)
        y+=1;
     else
        *mv=LEFT;
     return 0;
left:if(x>X_MIN)
        x-=1;
     else
        *mv=UP;
     return 0;
right:if(x<X_MAX)
         x+=1;
      else
         *mv=DOWN;
      return 0;
return 0;
}

void show_scrn(light_t light)
{
    for(int i=0;i<y;i++)
       printf("\n");
    fflush(stdout);
    light=light->next;
    while(light)
    {
       for(int j=0;j<x;j++)
          printf(" ");
       printf("%s",light->line);
       light=light->next;
    }
}

int light_flash(light_t light , int*n)
{
   if(*n>=ch_max)
     *n=0;
   int i=0,buf=*n;
   light=light->next;
   while(light)
   {
      for(;light->line[i]!=0 && i<=*n;i++)
         if(light->line[i]=='*')
	   light->line[i]='-';
	 else
	 if(light->line[i]=='-')
	   light->line[i]='*';
      if(i<*n)
      {
         light=light->next;
	 *n-=i;
	 i=0;
      }
      else
         break;
   }

   *n=buf+1;
return 0;
}

int light_read(light_t light , FILE*fd)
{
    if(!fd || !light)
      return -1;
    light_t p=light;
    light_t q=NULL;
    ch_max=0;
    while(!feof(fd))
    {
        q=(light_t)(malloc)(sizeof(struct light));
	if(q==NULL)
	  return -1;
	fgets(q->line,256,fd);
	p->next=q;
	q->next=NULL;
	p=q;
	ch_max+=strlen(q->line);
    }
    fclose(fd);
return 0;
}

int set_in_mode(int flag)
{
    static struct termios stty;
    static int org_flg;
if(flag==1)
{
    if(tcgetattr(0,&stty))
    {
        printf("Error:get tty mode\n");
        return -1;
    }
    stty.c_lflag&=~ICANON;
    stty.c_lflag&=~ECHO;
    if(tcsetattr(0,TCSANOW,&stty))
    {
       printf("Error:reset tty mode\n");
       return -1;
    }
    int fg;
    org_flg=fg=fcntl(0,F_GETFL);
    fg|=O_NDELAY;
    if(fcntl(0,F_SETFL,fg))
    {
       printf("Error:set in mode\n");
       perror("fcntl");
       return -1;
    }
}
else
if(flag==0)
{
   stty.c_lflag|=ECHO;
   stty.c_lflag|=ICANON;
   if(fcntl(0,F_SETFL, org_flg)==-1)return -1;
return tcsetattr(0 , TCSANOW , &stty);
}
else
   return -1;

return 0;
}
