#ifndef SET_TTY_H
#define SET_TTY_H

#include <termios.h>

struct termios stty;

int set_in_mode(int);

#endif
