#ifndef SDEF_H
#define SDEF_H


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define ERR_EMPT    13
#define ERR_OVER    14

#define BODY_MLEN   287
#define BODY      '$'
#define HEAD      '@'
#define BODY_PZ     '&'

#define INIT_LEN    2


#define AREA_X      47
#define AREA_Y      18

#define INIT_X      3
#define INIT_Y      3

#define FOOD_IX     43
#define FOOD_IY     3

#define SCOR_FOOD   3
#define SCOR_PRIZ   7

#define UP          'w'
#define DOWN        's'
#define LEFT        'a'
#define RIGHT       'd'
#define QUIT        'k'
#define PASUE       ' '

#define SPEED_DEF   204800
#define SPEED_MAX   81920
#define SPEED_MIN   409600

#define ST_DEAD     1
#define ST_LIVE     0

#define TIMER       16384

#define FOOD        'o'
#define PRIZE       'S'

#define MODE_BASIC  1
#define MODE_SIMPL  2
#define MODE_HARD   3
#define MODE_FUCK   4

#define START_MODE  0
#define END_MODE    1

#define INST_STR    "wsad"

#define PRIZ_TIME   73

int head_x;
int head_y;
int last_x;
int last_y;
int pz_y;
int pz_x;
char priz_st;
char move_to;
char sflag_buf;
char snake_state;
char self_flag;

struct snk_pos
{
    int px;
    int py;
};

#define PRIZE_COUNT     8
#define FOOD_SCORE      4
#define PRIZ_SCORE      8

#define WHAT_FOOD       1
#define WHAT_PRIZ       2

struct snk_info
{
    int blen;
    int score;
    int food_count;
    int priz_count;
    int speed;
    char head;
    char body;
    struct snk_pos sp[BODY_MLEN+1];
};

#define SCR_UNUS    0
#define SCR_SNAK    1
#define SCR_FOOD    2
#define SCR_PRIZ    3
#define SCR_WALL    4

struct scr_info
{
    int fy;
    int fx;
    char scr[AREA_Y+1][AREA_X+1];
    char sflag[AREA_Y+1][AREA_X+1];
};


int init_info(struct snk_info*, struct scr_info*);

int get_mode(struct scr_info*, int);

int out_info(struct snk_info*, struct scr_info*);

int upd_info(struct snk_info*, struct scr_info*);

int prod_fdpz(struct scr_info*, int);

int move(struct snk_info*, char );

int game_start();

int set_imode(struct termios*, int);

int creat_scrn(struct scr_info*);

int simple(struct scr_info*);

int hard(struct scr_info*);

int fuck(struct scr_info*);

#endif

