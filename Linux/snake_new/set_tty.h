#ifndef SET_TTY_H
#define SET_TTY_H


#include	<termios.h>

#define MD_ON	1
#define MD_OFF	0

int set_tty(struct termios*tty, int* in_mode, int mode);


#endif
