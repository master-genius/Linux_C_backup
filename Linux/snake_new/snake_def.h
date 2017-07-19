#ifndef SNAKE_DEF_H
#define SNAKE_DEF_H


#define UP		'w'
#define DOWN		's'
#define LEFT		'a'
#define RIGHT		'd'
#define QUIT		'q'
#define PAUSE		' '
#define UP_SPEED	'+'
#define DOWN_SPEED	'-'
#define SNAKE		"$ss"
#define SN_STLEN	3

#define FOOD        'o'
#define BODY        's'

#define MV_CMD		"wasd"
#define ALL_CMD		"wasd+-q"

#define X_MAX		47
#define Y_MAX		23
#define X_MIN		0
#define Y_MIN		0
#define X_EDGE		"         "
#define Y_EDGE		"\n\n"
#define LEN_MAX		128

#define X_START		3
#define Y_START		13

#define ONE_SCORE	7
#define PZ_COM_SCOR	13
#define PZ_KILL_SCOR	18

#define FOOD_START_X	32
#define FOOD_START_Y	13

#define FOOD_YES	1
#define FOOD_NO		0

#define PRIZE_YES	1
#define PRIZE_NO	0
#define PRIZE_WAIT	2


#define PZ_COM		'O'
#define PZ_KILL		'k'

#define SPEED		256000
#define NEXT		32000

#define PRIZE_TIME	75
#define SCORE_PRIZE	9


#define D_MNUM		7
#define DEAD		"|*=-"

#define DEAD_ONE	'|'
#define DEAD_TWO	'='
#define DEAD_THR	'-'
#define DEAD_FOU	'*'

#define RAND_TWO	13


struct snake_prcd
{
   int x_n;
   int y_n;
};

struct food
{
   int fo_x;//the position of food in x
   int fo_y;//the position of food in y
   int pr_x;
   int pr_y;
   int fg_prize;
   int fg_food;
   int pz_time;
   //int pz_nm;
   char pz_type;
};

struct count
{
   char p_name[32];
   int score;
   int nm_prize;
   int nm_score;
   int level;
   int len;
};

struct all_info
{
	//snake speed
	int speed;

	//direction
	char mv;

	//the position of last pointer in x
	int x_last;

	//the position of last pointer in y
	int y_last;

	//prize position in x
	int x_pz_old;

	//prize position in y
	int y_pz_old;

	//the length of snake
	int len_now;

	//the screen of game

	int blood;

	//food and prize infromation
	struct food fod_pz;

	//snake
	char snake[LEN_MAX];

	//snake information in all the position
	struct snake_prcd sk[LEN_MAX];

	//player information
	struct count usr;

};


#endif
