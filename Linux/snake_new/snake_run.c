#include	"snake.h"
#include	"snake_def.h"
#include	"set_tty.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>

int snake_run()
{
	struct termios tty;

	char scrn[Y_MAX][X_MAX+1];

	int in_mode;

	struct all_info sall;

	char *pps[Y_MAX];

	for(int i=0;i<Y_MAX;i++)
		pps[i]=scrn[i];

	char** pc=pps;

	//snake_login(&sall);

	if(init_scrn(&sall,pc)==-1)
		return -1;

	int level=0;
	
	printf("choose a level->[1,2,3,4]_>");
	
	if(scanf("%d",&level)!=1)level=0;
	
	if(level>4 || level<0)level=0;

	if(next_level(level,pc)==-1)return -1;

	if(set_tty(&tty, &in_mode, MD_ON))
		return -1;

	char cmd=0;

	char buf=0;

	out_scrn(&sall,pc);
	fflush(stdout);

	while(1)
	{
		cmd=getchar();

   		if(strchr(ALL_CMD,cmd) && cmd!=sall.mv)
   		{
   		    sall.mv=cmd;

   		    if(strchr(MV_CMD,cmd))
			buf=cmd;
   		}

		if(sall.mv==QUIT) break;

		if(upd_scrn(&sall,pc)==-1)
			break;

		if(snake_food(&sall, pc)==-1)
			break;

		out_scrn(&sall,pc);
		fflush(stdout);

		usleep(sall.speed-100);

		clr_scrn();

		if(!strchr(MV_CMD,sall.mv))
			sall.mv=buf;

	}
	
	end:;

	return set_tty(&tty,&in_mode, MD_OFF);

return 0;
}
/*s
int snake_login(struct all_info*sall)
{
	if(sall==NULL)
		return -1;

    (sall->usr).score=0;
    (sall->usr).nm_score=0;
    (sall->usr).nm_prize=0;
    (sall->usr).level=0;
    (sall->usr).len=SN_STLEN;

    printf("login_>");
    fgets((sall->usr).p_name,32,stdin);

    for(int i=0;(sall->usr).p_name[i]!=0;i++)
       if((sall->usr).p_name[i]=='\n')
          (sall->usr).p_name[i]=0;

return 0;
}
*/

void clr_scrn()
{
   printf("\x1b[2J\x1b[;H");
   fflush(stdout);
}

