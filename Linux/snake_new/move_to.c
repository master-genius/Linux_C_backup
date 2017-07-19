#include	"snake_def.h"
#include	"snake.h"
#include	<string.h>


int move_to(struct all_info*sall, char**scrn)
{
	if(!scrn|| !sall)
		return -1;

	switch(sall->mv)
	{
		case UP:
			{

				if((sall->sk[0]).y_n > Y_MIN)
					(sall->sk[0]).y_n-=1;
				else
					return -1;
			}break;
		
		case DOWN:
			{
				if((sall->sk[0]).y_n < Y_MAX)
					(sall->sk[0]).y_n += 1;
				else
					return -1;
			}break;
			
		case LEFT:
			{
				if((sall->sk[0]).x_n > X_MIN)
					(sall->sk[0]).x_n -= 1;
				else
					return -1;

			}break;
		
		case RIGHT:
			{
				if((sall->sk[0]).x_n<X_MAX)
					(sall->sk[0]).x_n+=1;
				else
					return -1;
			}break;
		
		case UP_SPEED:
			{
				if(sall->speed>NEXT)
					sall->speed -=NEXT;
			}break;
		
		case DOWN_SPEED:
			{
				if(sall->speed<SPEED)
					sall->speed +=NEXT;
			}break;

		default: ;

	}

	if(strchr(DEAD,scrn[(sall->sk[0]).y_n][(sall->sk[0]).x_n]))
	{
		sall->blood--;
		if(sall->blood<0)
			return -1;
		(sall->usr).score-=PZ_KILL_SCOR;
	}

return 0;
}
