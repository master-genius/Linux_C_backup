#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define NM_MIN      2
#define NM_MAX      41
#define NM_UP       7
#define NM_MAX_ST   20

#define SPEED_DEF   409600
#define SPEED_MAX   204800
#define SPEED_UP    12800

#define SCRN_Y      23
#define SCRN_X      47

#define SCRN_UP     '-'
#define SCRN_DOWN   '-'
#define SCRN_LEFT   '|'
#define SCRN_RIGHT  '|'

#define PROD_TIME   5

#define FR_PREC     0.02

#define BIT_MASK    240

#define X_LEFT      0
#define X_RIGHT     (X_LEFT+SCRN_X)
#define Y_UP        0
#define Y_DOWN      (Y_UP+SCRN_Y)

#define EXP_MAX     1024
#define EXP_IN      5
#define EXP_UP      29

#define SCORE_MIN   7
#define SCORE_MAX   11
#define SCORE_UP    2

#define ERR_MEM     1
#define ERR_INIT    2
#define ERR_IEXP    3
#define ERR_EWIN    4
#define ERR_EMPT    5

int err_code;

#define OPER        "*/+-"
#define OP_LEN      4

#define EXP_MLEN    13

struct exp_list
{
    int a;
    int b;
    int r;
    double fr;
    //char*rstr;
    //char*sr;
    int pos_y;
    int pos_x;
    char oper;
    int score;
    char exp[EXP_MLEN];
    struct exp_list* next;
    struct exp_list* prev;
};

struct exp_ctl
{
    struct exp_list* head;
    unsigned int count;
    unsigned int speed;
};

#define NAME_MAX    32

struct player
{
    unsigned int count;
    unsigned int consecutive;
    unsigned int con_max;
    unsigned int total_score;
    unsigned int score;
    double fast;
    double corr_perc;
    char name[NAME_MAX+1];
};

#define RESULT_MAX      32
/*define global varibles*/
char res[RESULT_MAX+1];

char get_flag;

unsigned int exp_count;

int min;

int max;

int score_now;

int speed_now;

char quit;
/*end define*/

/*define functions*/
int init_scrn();

int init_exp(struct exp_ctl*ec);

int prod_exp(struct exp_ctl*ec, int );

int judg_exp(struct exp_ctl*ec,struct player*py);

int update(struct exp_ctl*);

int rm_exp(struct exp_ctl*, struct exp_list*);

int py_get(struct exp_list*, struct player*);

int get_in();

int out_scrn(struct exp_ctl*,struct player*);

void des_exp_list(struct exp_ctl*ec);

int hand(int );

/*end define*/

int main()
{
    pthread_t th1 , th2;

    if(init_scrn()==-1)return -1;

    if(pthread_create(&th1,NULL,(void*)get_in,NULL)==-1)
    {
        perror("pthread_create");
        return -1;
    }

    if(pthread_create(&th2,NULL,(void*)hand,NULL)==-1)
    {
        perror("pthread_create");
        return -1;
    }

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

return 0;
}


int init_scrn()
{
    if(initscr()==NULL)
    {
        err_code=ERR_INIT;
        return -1;
    }
    //raw();
    //nodelay(stdscr,TRUE);

    speed_now=SPEED_DEF;
    score_now=SCORE_MIN;
    get_flag=0;
    min=NM_MIN;
    max=NM_MAX_ST;
    exp_count=0;
    quit=0;
    bzero((void*)res,sizeof(char)*RESULT_MAX);
return 0;
}

int init_exp(struct exp_ctl*ec)
{
    if(!ec)
    {
        err_code = ERR_EMPT;
        return -1;
    }

    struct exp_list*p,*q;
    p=q=NULL;

    ec->head=(struct exp_list*)malloc(sizeof(struct exp_list));
    if(!ec->head)
    {
        perror("malloc");
        err_code = ERR_MEM;
        return -1;
    }
    ec->head->next = NULL;
    ec->head->prev = NULL;

    ec->count=0;
    ec->speed=0;

    int i=0;
    int seed=0;
    while(i<EXP_IN)
    {
        seed+=3;
        if(prod_exp(ec, seed)==-1)
        {
            des_exp_list(ec);
            return -1;
        }
        i++;
    }

    ec->speed=speed_now;

return 0;
}

int prod_exp(struct exp_ctl*ec, int seed)
{
    if(!ec || !ec->head)
    {
        err_code = ERR_EMPT;
        return -1;
    }

    struct exp_list*p,*q;
    p=q=NULL;

    p=(struct exp_list*)malloc(sizeof(struct exp_list));
    if(!p)
    {
        perror("malloc");
        err_code = ERR_MEM;
        return -1;
    }
    srand((int)time(0)+seed);
    p->a=(rand()%max)+min;

    srand((int)time(0)+1+seed);
    p->b=(rand()%max)+min;

    srand((int)time(0)+2*seed);
    int op = rand()%OP_LEN;
    if(op<0  || op>=OP_LEN)
        op=0;

    p->oper = OPER[op];

    p->score=0;
    switch(p->oper)
    {
        case '+':
        {
            p->r = p->a + p->b;
        }break;

        case '-':
        {
            p->r = p->a - p->b;
        }break;

        case '*':
        {
            p->r = p->a * p->b;
            p->score=3;
        }break;

        case '/':
        {
            p->fr = (1.0*p->a) / (1.0*p->b);
            p->score=4;
        }break;

        default:;

    }

    bzero((void*)p->exp,sizeof(char)*EXP_MLEN);
    int db=0, gb=0;
    int i=0;
    db=p->a / 10;
    gb=p->a - db*10;
    if(db>0)
        p->exp[i++]=db+48;
    if(gb>0)
        p->exp[i++]=gb+48;

    p->exp[i++]=p->oper;

    db=p->b / 10;
    gb=p->b-db*10;

    if(db>0)p->exp[i++]=db+48;
    if(gb>0)p->exp[i++]=gb+48;
    p->exp[i]=0;

    p->pos_y = 0;

    srand((int)time(0)+3*seed);

    p->pos_x = (rand()%(X_RIGHT-7)) + X_LEFT+1;

    p->score += score_now;

    q=ec->head->next;
    ec->head->next=p;
    p->next=q;
    p->prev=ec->head;
    if(q)q->prev=p;
    p=q=NULL;

    ec->count++;
    exp_count++;
return 0;
}

int judg_exp(struct exp_ctl*ec,struct player*py)
{
    if(!ec || !ec->head || !py)
    {
        err_code = ERR_EMPT;
        return -1;
    }

    struct exp_list* p=NULL;


    int r=-1;
    double fr=-1;
    for(p=ec->head->next;p!=NULL;p=p->next)
    {
        if(p->oper=='/')
        {
            fr=atof(res);
            if(p->fr>=(fr-FR_PREC) && p->fr<=(fr+FR_PREC))
            {
                py_get(p,py);
                rm_exp(ec,p);
                return 0;
            }
        }
        else
        {
            r = atoi(res);
            if(p->r==r)
            {
                py_get(p,py);
                rm_exp(ec,p);
                return 0;
            }
        }
    }

    bzero((void*)res,sizeof(char)*RESULT_MAX);
    py->con_max = py->consecutive;
    py->consecutive=0;

return 0;
}

int rm_exp(struct exp_ctl*ec,struct exp_list*p)
{

    struct exp_list* buf_a=NULL , *buf_b=NULL;

    ec->count--;
    buf_a = p->prev;
    buf_b = p->next;
    buf_a->next=buf_b;
    if(buf_b)buf_b->prev = buf_a;
    free(p);

return 0;
}


int py_get(struct exp_list*p, struct player*py)
{
    if(!p || !py)return -1;

    py->score += p->score;
    py->consecutive++;
    py->count++;
    py->total_score += score_now;
    py->fast = ((double)(py->score)) / ((double)(py->total_score));
    py->corr_perc = ((double)py->count) / ((double)exp_count);

    if(!(py->count%EXP_UP))
    {
        if(max<NM_MAX)
        {
            max+=NM_UP;
        }
        if(speed_now>SPEED_MAX)speed_now -= SPEED_UP;

        if(score_now<SCORE_MAX)score_now += SCORE_UP;
    }

return 0;
}


int update(struct exp_ctl*ec)
{
    if(!ec || !ec->head)
    {
        err_code = ERR_EMPT;
        return -1;
    }

    struct exp_list* p=NULL;
    struct exp_list* b=NULL, *c = NULL;

    for(p=ec->head->next;p!=NULL;p=p->next)
    {
        p->pos_y++;

        if(p->pos_y >= Y_DOWN)
            rm_exp(ec,p);
        else if(p->pos_y >= ((Y_DOWN/2)+1))
            p->score--;

    }

return 0;
}

int get_in()
{
    int i=0;
    char c=0;
    res[0]=0;
/*
    while(!quit)
    {
        c=getch();
        if(c>0 && i< RESULT_MAX && i>=0 && get_flag==0)
        {
            if(c=='\n')
            {
                res[i]=0;
                get_flag=1;
            }
            else if(c==8 || c==127)
            {
                if(i>0){i--;res[i]=0;}
            }
            else if((c>='0' && c<='9')||c=='.')
            {
                res[i]=c;i++;
                res[i]=0;
            }
            else if(c=='q')
            {
                quit=1;
            }
        }
    }
*/

    while(!quit)
    {
        if(get_flag==0)
        {
            bzero((void*)res,RESULT_MAX*sizeof(char));
            getnstr(res,RESULT_MAX);
            get_flag=1;
            if(strcmp(res,"q")==0)quit=1;
        }
        else usleep(70);
    }

return 0;
}

int out_scrn(struct exp_ctl*ec, struct player*py)
{
    if(!ec || !ec->head || !py)
    {
        err_code = ERR_EMPT;
        return -1;
    }

    int i=0;

    for(i=X_LEFT;i<X_RIGHT;i++)
    {
        mvaddch(Y_UP,i,SCRN_UP);
        mvaddch(Y_DOWN,i,SCRN_DOWN);
    }

    for(i=Y_UP;i<Y_DOWN;i++)
    {
        mvaddch(i,X_LEFT,SCRN_LEFT);
        mvaddch(i,X_RIGHT,SCRN_RIGHT);
    }

    mvaddstr(Y_UP,X_RIGHT+1,py->name);

    move(Y_UP+1,X_RIGHT+1);
    printw("score:%d",py->score);

    move(Y_UP+2,X_RIGHT+1);
    printw("fast:%g",py->fast);

    move(Y_UP+3,X_RIGHT+1);
    printw("corect percent:%g",py->corr_perc);

    move(Y_UP+4,X_RIGHT+1);
    printw("consecutive max:%d",py->con_max);

    move(Y_UP+5,X_RIGHT+1);
    printw("consecutive:%d",py->consecutive);

    move(Y_UP+6,X_RIGHT+1);
    printw("counts:%d",py->count);

    struct exp_list* p=NULL;

    //int bits=0;
    for(p=ec->head->next;p!=NULL;p=p->next)
    {
        mvaddstr(p->pos_y,p->pos_x,p->exp);
        /*
        move(p->pos_y,p->pos_x);
        printw("%d",p->a);
        bits=1;
        if(BIT_MASK&p->a)bits++;
        move(p->pos_y,p->pos_x+bits);
        printw("%c",p->oper);

        move(p->pos_y,p->pos_x+bits+3);
        printw("%d",p->b);*/
    }

    mvaddch(Y_DOWN+1,X_LEFT,'_');
    //mvaddstr(Y_DOWN+1,X_LEFT+1,res);
    refresh();

return 0;
}

void des_exp_list(struct exp_ctl*ec)
{
    if(!ec || !ec->head)return ;

    struct exp_list*p,*q;

    q=p=ec->head;

    while(p)
    {
        q=q->next;
        free(p);
        p=q;
    }
    p=q=NULL;
}

int hand(int arg)
{

    struct exp_ctl ec;
    struct player py;

    bzero((void*)&py,sizeof(py));

    //if(init_scrn()==-1)return -1;

    if(init_exp(&ec)==-1)return -1;

    strncpy(py.name,"Brain",5);
    py.name[5]=0;

    if(out_scrn(&ec,&py))
    {
        des_exp_list(&ec);
        return -1;
    }
/**/
    int T=0,seed=0;

    while(!quit)
    {
        seed++;
        if(get_flag==1)
        {
            if(judg_exp(&ec,&py))break;
            get_flag=0;
        }
        clear();
        if(update(&ec))break;
        if(out_scrn(&ec,&py))break;
        usleep(speed_now);
        T++;
        if(T==PROD_TIME)
        {
            if(prod_exp(&ec,seed)==-1)break;
            T=0;
        }
    }

    des_exp_list(&ec);
    endwin();

return 0;
}
