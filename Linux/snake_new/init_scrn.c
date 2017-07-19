#include	"snake.h"
#include	"snake_def.h"
#include	<string.h>


int init_scrn(struct all_info*sall, char** scrn)
{
	if(sall==NULL || scrn==NULL)
		return -1;

	for(int i=0;i<X_MAX;i++)
		scrn[0][i]='_';

	for(int i=1;i<Y_MAX-1;i++)
	{
		scrn[i][0]='|';
		for(int j=1;j<X_MAX-1;j++)
			scrn[i][j]=' ';
		scrn[i][X_MAX-1]='|';
		scrn[i][X_MAX]=0;
	}

	for(int i=0;i<X_MAX;i++)
		scrn[Y_MAX-1][i]='*';

	scrn[0][X_MAX]=0;
	scrn[Y_MAX-1][X_MAX]=0;

	strcpy(sall->snake, SNAKE);

	sall->len_now=strlen(sall->snake);

	for(int i=0;i<sall->len_now;i++)
	{
		(sall->sk[i]).x_n=X_START+i;
		(sall->sk[i]).y_n=Y_START;
	}

	(sall->fod_pz).fo_x = FOOD_START_X;
	(sall->fod_pz).fo_y = FOOD_START_Y;
	(sall->fod_pz).fg_prize = PRIZE_NO;

	scrn[(sall->fod_pz).fo_y][(sall->fod_pz).fo_x]='$';

	sall->x_last = (sall->sk[sall->len_now-1]).x_n;

	sall->y_last = (sall->sk[sall->len_now-1]).y_n;

	sall->speed=SPEED;

	sall->blood=0;

	(sall->fod_pz).fg_food=FOOD_YES;

return 0;
}
