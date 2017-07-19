#include	"snake_def.h"
#include	"snake.h"
#include	<stdio.h>

int out_scrn(struct all_info*sall, char**scrn)
{
	if(!scrn || !sall)
		return -1;

	printf("%s",Y_EDGE);
	for(int i=0;i<Y_MAX;i++)
	{
		printf("%s%s\n",X_EDGE,scrn[i]);
		fflush(stdout);
	}
	printf("%s score:%d",X_EDGE,(sall->usr).score);
	fflush(stdout);

return 0;
}
