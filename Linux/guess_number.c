#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>

#define ROW_NUM 3

static struct termios orig;
static int game_number=0;
static int mid_line;

int game_start();
void game_out(int *game[]);
void game_start_out(int*game[]);
int game_run();
int game_cal(int,int**);
int game_end();
int get_number();
int get_midline();

int main()
{
   get_number();
   if(game_start()!=0)
     return 1;
   if(game_run()!=0)
     return 2;
   if(game_end()!=0)
     return 3;
return 0;
}

int game_start()
{
   if(tcgetattr(0,&orig)==-1)
   {
      printf("error to get tty setting\n");
      return -1;
   }
   orig.c_lflag&=~ICANON;
   if(tcsetattr(0,TCSANOW,&orig)==-1)
   {
       printf("reset tty to fail\n");
       return -1;
   }
return 0;
}

void game_out(int*game[])
{
    for(int i=0;i<ROW_NUM;i++)
    {
       printf("%d: ",i+1);
       for(int j=0;j<game_number;j++)
          printf("%3d  ",game[i][j]);
       printf("\n");
    }
}

int game_run()
{
   int loop=0;
   int total=game_number*3;
   for(;total>0;total/=3)
     loop++;
   if(game_number>81)
     loop++;
   int data=0;
   int*game[ROW_NUM];
   for(int i=0;i<ROW_NUM;i++)
   {
     game[i]=(int*)malloc(sizeof(int*)*game_number);
     if(game[i]==NULL)
     {
        for(int j=0;j<i;j++)
	   free(game[j]);
	return -1;
     }
   }
   for(int i=0;i<ROW_NUM;i++)
      for(int j=0;j<game_number;j++)
         game[i][j]=data++;
   game_start_out(game);
   printf("choosing a number and remember it\npress <enter> to continue..\n");
   getchar();
   printf("\x1b[2J\x1b[;H");
   for(int i=0;i<loop;i++)
   {
      game_out(game);
      if(get_midline()==-1)
      {
         printf("game fail\n");
	 return -1;
      }
      game_cal(mid_line,game);
      printf("\x1b[2J\x1b[;H");
   }
   printf("your number:%d\n",game[mid_line-1][game_number/2]);
return 0;
}

int game_cal(int mid,int*game[])
{
    if(mid<1 || mid>3)
        return -1;
    if(!game)
        return -1;

    mid--;
    if(mid!=1)
    {
	int p=0;
	for(int i=0;i<game_number;i++)
	{
       	     p=game[1][i];
	     game[1][i]=game[mid][i];
	     game[mid][i]=p;
	}
    }
    char tmp[game_number][3];
    int lsp=0;
    int asp=0;
    for(int i=0;i<3;i++)
       for(int j=0;j<game_number;j++)
       {
   	    if(asp>2)
		asp=0;
	    tmp[lsp][asp]=game[i][j];
	    if(asp==2)
		lsp++;
	    asp++;
       }
    asp=0;lsp=0;
    for(int i=0;i<3;i++)
	for(int j=0;j<game_number;j++)
	{
	   if(lsp>=game_number)
		lsp=0;
	   game[i][j]=tmp[lsp][asp];
	   if(lsp==game_number-1)
		asp++;
	   lsp++;
	}
return 0;
}

int game_end()
{
   orig.c_lflag|=ICANON;
   return tcsetattr(0,TCSANOW,&orig);
}

int get_number()
{
   printf("get a number_>");
   char c=0;
   scanf("%d",&game_number);
   while((c=getchar())!='\n');
   if(game_number<4)
      game_number=5;
   if(game_number%2==0)
     game_number+=1;
return 0;
}

int get_midline()
{
    for(int i=0;i<5;i++)
    {
       printf("where is line your number in?");
       mid_line=getchar();
       if(mid_line>'3'||mid_line<'1')
          printf("error:it mustbe 1 2 3\n");
       else
       {
          mid_line-=48;
          return 0;
       }
    }
     printf("You are so stupid\ngame over\n");
return -1;
}

void game_start_out(int*game[])
{
    int ln=0;
    for(int i=0;i<ROW_NUM;i++)
       for(int j=0;j<game_number;j++)
       {
           ln++;
           printf("%3d  ",game[i][j]);
	   if(ln==4)
	   {
	       printf("\n");
	       ln=0;
	   }
       }
    printf("\n");
}
