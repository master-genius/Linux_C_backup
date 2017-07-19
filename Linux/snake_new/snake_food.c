#include	"snake_def.h"
#include	"snake.h"
#include	<time.h>
#include	<stdlib.h>

int snake_food(struct all_info*sall, char** scrn)
{
	if(!scrn || !sall)
		return -1;

	if((sall->fod_pz).fg_food == FOOD_YES)
		goto prize;

	(sall->fod_pz).fo_x=rand_num(X_MAX,0);
	(sall->fod_pz).fo_y=rand_num(Y_MAX,0);

	if((sall->fod_pz).fo_x<=0 || (sall->fod_pz).fo_x >= X_MAX)
		(sall->fod_pz).fo_x = 1;
	
	if((sall->fod_pz).fo_y <= 0 || (sall->fod_pz).fo_y >= Y_MAX)
		(sall->fod_pz).fo_y = 1;
	
	if(scrn[(sall->fod_pz).fo_y][(sall->fod_pz).fo_x] != ' ')
		for(int i=1;i<X_MAX;i++)
			for(int j=1;j<Y_MAX;j++)
				if(scrn[j][i]==' ')
				{
					(sall->fod_pz).fo_x=i;
					(sall->fod_pz).fo_y=j;
					goto out_loop;
				}
	
	out_loop:;
	
	scrn[(sall->fod_pz).fo_y][(sall->fod_pz).fo_x]=FOOD;

	(sall->fod_pz).fg_food = FOOD_YES;

	prize:;

	if((sall->fod_pz).fg_prize == PRIZE_YES)
	{
		(sall->fod_pz).pr_x = rand_num(X_MAX,1);
		(sall->fod_pz).pr_y = rand_num(Y_MAX,1);
		
		if((sall->fod_pz).pr_x <= 0 || (sall->fod_pz).pr_x >= X_MAX)
			(sall->fod_pz).pr_x = 1;

		if((sall->fod_pz).pr_y <= 0 || (sall->fod_pz).pr_y >= Y_MAX)
			(sall->fod_pz).pr_y = 1;

		if(scrn[(sall->fod_pz).pr_y][(sall->fod_pz).pr_x]!=' ')
			for(int i=1;i<X_MAX;i++)
				for(int j=1;j<Y_MAX;j++)
					if(scrn[j][i]==' ')
					{
						(sall->fod_pz).pr_x=i;
						(sall->fod_pz).pr_y=j;
						goto out;
					}
		
		out:;
		
		int pz=rand_num(9,13);

		scrn[(sall->fod_pz).pr_y][(sall->fod_pz).pr_x]=(pz<6)?PZ_COM:PZ_KILL;
		(sall->fod_pz).pz_type=scrn[(sall->fod_pz).pr_y][(sall->fod_pz).pr_x];
		sall->x_pz_old = (sall->fod_pz).pr_x;
		sall->y_pz_old = (sall->fod_pz).pr_y;
		(sall->fod_pz).fg_prize=PRIZE_WAIT;
		(sall->fod_pz).pz_time = PRIZE_TIME;
	}

return 0;
}

int rand_num(int mx,int sd)
{
    srand((int)time(0)+sd);
return ((rand()%mx)<=0)?1:(rand()%mx);
}
