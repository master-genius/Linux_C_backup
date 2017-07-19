#include	"snake_def.h"
#include	"snake.h"
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<time.h>

int next_level(int level, char**scrn)
{
	if(!scrn)
		return -1;
	
	switch(level)
	{
		case 1:
		{
			int lnl = X_MAX/3;
			int lnr = X_MAX-lnl;
			
			int up = Y_MAX/3;
			
			int down = Y_MAX-up;
			
			for(int i=lnl;i<lnr;i++)
				scrn[up][i]=scrn[down][i]=DEAD_TWO;
			
			for(int k=up;k<down;k++)
				scrn[k][lnl]=DEAD_ONE;
			
		}break;

		case 2:
		{
			int k=0;
			
			char dd[D_MNUM];
			
			strcpy(dd,DEAD);
			
			int y=3;
			int x=3;
			for(int i=0;i<RAND_TWO;i++)
			{
				if(dd[k]==0)k=0;
				
				srand((int)time(0)+i);
				y=rand()%(Y_MAX-5);
				
				srand((int)time(0)+i+1);
				x=rand()%(X_MAX-9);
				
				if(y<1 || y>Y_MAX-5) y=Y_MAX/3 + i;
				
				if(x<1 || x>X_MAX-9) x=X_MAX/3 + i;
				
				if(scrn[y][x]==' ') scrn[y][x]=dd[k++];
			}
		}break;
		
		case 3:
		{
			
		}break;
		
		case 4:
		{
			
		}break;
		
		default: ;
	}

return 0;
}


/*
int next_level(int level)
{
   if(level==0)
     return 0;
   if(level==1)
      goto one;
   if(level==2)
      goto two;
   if(level==3)
     goto three;
   if(level==4)
	goto four;
   return -1;
one:for(int i=4;i<10;i++)
    {
       scrn[i][FOOD_START_X-3]=FAIL_ONE;
       scrn[i][FOOD_START_X+3]=FAIL_ONE;
    }
    return 0;

two:for(int i=4;i<10;i++)
    {
       scrn[2][i]=FAIL_TWO;
       scrn[18][i]=FAIL_TWO;
    }
    goto one;

three:scrn[11][20]=FAIL_ONE;
      scrn[15][20]=FAIL_ONE;
      for(int i=40;i<48;i++)
         scrn[12][i]=FAIL_TWO;
      scrn[12][43]=scrn[12][44]=' ';
      for(int i=4;i<10;i++)
         scrn[i][53]=FAIL_ONE;
      goto two;

four:for(int i=LELM_MIN_Y,j=LELM_MIN_X;\
	i<LELM_MAX_Y && j<LELM_MAX_X;i++,j++)
		scrn[i][j]=FAIL_THREE;
	goto three;
}
*/