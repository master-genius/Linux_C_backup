#include	"snake_def.h"
#include	"snake.h"
//#include

int upd_scrn(struct all_info*sall, char** scrn)
{
	if(!sall || !scrn) return -1;

	if((sall->sk[0]).x_n<=X_MIN || (sall->sk[0]).x_n>=X_MAX-1)
		return -1;
	if((sall->sk[0]).y_n<=Y_MIN || (sall->sk[0]).y_n>=Y_MAX-1)
		return -1;

	sall->x_last=(sall->sk[sall->len_now-1]).x_n;
	sall->y_last=(sall->sk[sall->len_now-1]).y_n;

	for(int i=sall->len_now-1;i>0;i--)
	{
		(sall->sk[i]).x_n=(sall->sk[i-1]).x_n;
		(sall->sk[i]).y_n=(sall->sk[i-1]).y_n;
	}

	for(int i=0;i<(sall->len_now)-1;i++)
		scrn[(sall->sk[i]).y_n][(sall->sk[i]).x_n]=sall->snake[i];

	scrn[(sall->sk[sall->len_now-1]).y_n][(sall->sk[sall->len_now-1]).x_n]=' ';

	if(move_to(sall,scrn)==-1)
		return -1;

	scrn[(sall->sk[0]).y_n][(sall->sk[0]).x_n]=sall->snake[0];


	if((sall->fod_pz).fo_x==(sall->sk[0]).x_n)
		if((sall->fod_pz).fo_y==(sall->sk[0]).y_n)
			if(sall->len_now<LEN_MAX)
			{
				sall->snake[(sall->len_now)++]=BODY;
				sall->snake[sall->len_now]=0;
				(sall->sk[sall->len_now-1]).x_n=sall->x_last;
				(sall->sk[sall->len_now-1]).y_n=sall->y_last;
				(sall->usr).nm_score++;
				(sall->usr).score+=ONE_SCORE;
				if((sall->usr).nm_score >= SCORE_PRIZE)
				{
					(sall->fod_pz).fg_prize=PRIZE_YES;
					(sall->usr).nm_score = 0;
				}
				(sall->fod_pz).fg_food = FOOD_NO;
			}

	if((sall->fod_pz).fg_prize==PRIZE_WAIT)
	{
		if((sall->fod_pz).pr_x==(sall->sk[0]).x_n)
			if((sall->fod_pz).pr_y==(sall->sk[0]).y_n)
			{
				if(sall->len_now<LEN_MAX)
				{
					sall->snake[sall->len_now++]=BODY;
					sall->snake[sall->len_now]=0;
					(sall->sk[sall->len_now-1]).x_n = sall->x_last;
					(sall->sk[sall->len_now-1]).y_n = sall->y_last;
				}

				if((sall->fod_pz).pz_type==PZ_KILL)
				{
					(sall->usr).score+=PZ_KILL_SCOR;
					sall->blood++;
				}
				else
					(sall->usr).score+=PZ_COM_SCOR;
				
				(sall->fod_pz).fg_prize=PRIZE_NO;
				(sall->fod_pz).pz_time=0;
				
			}

		if((sall->fod_pz).pz_time>0)
			(sall->fod_pz).pz_time--;
        else
        if((sall->fod_pz).pz_time<=0)
        {
            (sall->fod_pz).fg_prize=PRIZE_NO;
            scrn[sall->y_pz_old][sall->x_pz_old]=' ';
        }
	}

return 0;
}
