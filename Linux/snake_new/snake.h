#ifndef SNAKE_H
#define SNAKE_H


#include	"snake_def.h"

void	clr_scrn();

int	move_to(struct all_info*, char** scrn);

int	init_scrn(struct all_info* sall, char**scrn);

int	snake_login(struct all_info* sall);

int	upd_scrn(struct all_info*sall, char**scrn);

int	out_scrn(struct all_info*sall, char**scrn);

int	snake_food(struct all_info*, char**);

int	rand_num(int,int);

int	next_level(int level, char**);

int	snake_run();

int	th_upd();

#endif
