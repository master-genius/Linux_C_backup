#include	"set_tty.h"
#include	<fcntl.h>
#include	<termios.h>
#include	<stdio.h>

int set_tty(struct termios* tty, int* in_mode, int mode)
{
	if(!tty || !in_mode)
		return -1;

	if(mode==MD_ON)
	{
		if(tcgetattr(0,tty))
		{
			perror("tcgetattr");
			return -1;
		}
		tty->c_lflag&=~ICANON;
		tty->c_lflag&=~ECHO;
		if(tcsetattr(0, TCSANOW, tty))
		{
			perror("tcsetattr");
			return -1;
		}
		int fg;
		*in_mode=fg=fcntl(0,F_GETFL);
		fg|=O_NDELAY;
		if(fcntl(0,F_SETFL,fg))
		{
			perror("fcntl");
			tty->c_lflag|=ECHO;
			tty->c_lflag|=ICANON;
			tcsetattr(0, TCSANOW, tty);
			return -1;
		}
		return 0;
	}
	else
	if(mode==MD_OFF)
	{
		tty->c_lflag|=ECHO;
		tty->c_lflag|=ICANON;
		fcntl(0,F_SETFL,*in_mode);
		return tcsetattr(0, TCSANOW, tty);
	}

return -1;
}
