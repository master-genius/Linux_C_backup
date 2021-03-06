#include <stdio.h>
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

#define SPEED_DEF   20480
#define SPEED_MAX   204800
#define SPEED_UP    12800

#define MSTR        "-----------------------"
#define ASTR        "***********************"
#define SSTR        "                       "

#define PROD_TIME   200
#define TIMES       100

#define FR_PREC     0.02

#define EXP_MAX     1024
#define EXP_IN      5
#define EXP_UP      29

#define SCORE_MLOW  4
#define SCORE_MIN   7
#define SCORE_MAX   11
#define SCORE_UP    2

int err_code;

int pptr;

#define OPER        "+-*/"
#define OP_LEN      4

#define EXP_MLEN    13

struct exp
{
    int a;
    int b;
    int r;
    double fr;
    char opera;
    int score;
};

struct player
{
    unsigned int count;
    unsigned int consecutive;
    unsigned int con_max;
    unsigned int total_score;
    unsigned int score;
    double fast;
    double corr_perc;

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

int prod_exp(struct exp*, int);

int judg_exp(struct exp*,struct player*py);

int py_get(struct exp*, struct player*);

int get_in();

int out_scrn(struct exp*,struct player*);

int hand();

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
    speed_now=SPEED_DEF;
    score_now=SCORE_MIN;
    get_flag=0;
    min=NM_MIN;
    max=NM_MAX_ST;
    exp_count=0;
    quit=0;
    pptr=0;
    bzero((void*)res,sizeof(char)*RESULT_MAX);
return 0;
}

int prod_exp(struct exp* p, int seed)
{
    if(!p)
        return -1;

    srand((int)time(0)+seed);
    p->a=(rand()%max)+min;

    srand((int)time(0)+1+seed);
    p->b=(rand()%max)+min;

    srand((int)time(0)+2*seed);
    int op = rand()%OP_LEN;
    if(op<0  || op>=OP_LEN)
        op=0;

    p->opera = OPER[op];

    p->score=0;
    switch(p->opera)
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
            //p->score=3;
        }break;

        case '/':
        {
            p->fr = (1.0*p->a) / (1.0*p->b);
            //p->score=4;
        }break;

        default:;

    }

    p->score += score_now;
    exp_count++;

return 0;
}

int judg_exp(struct exp*p,struct player*py)
{
    if(!p || !py)
        return -1;

    int r=-1;
    double fr=-1;

    int right=0;

    if(p->opera=='/')
    {
        fr=atof(res);
        if(p->fr>=(fr-FR_PREC) && p->fr<=(fr+FR_PREC))
        {
            py_get(p,py);
            right=1;
        }
    }
    else
    {
        r = atoi(res);
        if(p->r==r)
        {
            py_get(p,py);
            right=1;
        }
    }

    if(right==0)
    {
        if(py->con_max < py->consecutive)py->con_max = py->consecutive;
        py->consecutive=0;
    }

return 0;
}


int py_get(struct exp*p, struct player*py)
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

int get_in()
{
    char c=0;
    while(!quit)
    {
        c=0;
        pptr=0;
        if(get_flag==0)
        {
            while(c!='\n' && pptr<RESULT_MAX)
            {
                c=getchar();
                if(c!='\n')
                    res[pptr]=c;
                pptr++;
            }
            res[pptr]=0;
            if(res[0]=='q')quit=1;
            get_flag=1;
        }usleep(51200);
    }

return 0;
}

int out_scrn(struct exp*e,struct player*p)
{
    if(!e || !p)
        return -1;
/*
    printf("  score:%d %s counts:%d\n\n",p->score,MSTR,p->count);
    printf("  consecutive:%d ...\n",p->consecutive);
    printf("\n  -------------->%d%c%d<--------\n\n",e->a,e->opera,e->b);
    printf("                    ... con_max:%d\n",p->con_max);
    printf("  fast:%g %s correct percent:%g\n\n  _",p->fast,ASTR,p->corr_perc);
    fflush(stdout);
*/
    printf("%sscore: %d\n%scounts: %d\n",SSTR,p->score,SSTR,p->count);
    printf("        %d%c%d     \n",e->a,e->opera,e->b);
    printf("%sfast: %.2g\n%scorrect percent: %.2g\n",SSTR,p->fast,SSTR,p->corr_perc);
    printf("%sthe totally counts of expression:%d\n",SSTR,exp_count);
    printf("\n  _");
    fflush(stdout);
return 0;
}

int hand()
{

    struct exp e;
    struct player py;

    bzero((void*)&py,sizeof(py));

    int seed=0;

    int T=0;

    printf("\x1b[2J\x1b[;H");
    if(prod_exp(&e,1)==-1)return -1;
    if(out_scrn(&e,&py)==-1)return -1;

    while(!quit)
    {
        if(quit) break;
        seed++;
        loop: T++;
        usleep(speed_now);
        if(get_flag==1)
        {
            if(judg_exp(&e,&py))break;
            bzero((void*)res,sizeof(char)*RESULT_MAX);
            pptr=0;
            get_flag=0;
            T=PROD_TIME+1;
        }
        if(T<PROD_TIME){if((PROD_TIME-T)<=TIMES && e.score>SCORE_MLOW)e.score--;goto loop;}
        else T=0;

        printf("\x1b[2J\x1b[;H");
        fflush(stdout);
        bzero((void*)&e,sizeof(e));
        if(prod_exp(&e,seed)==-1)break;
        if(out_scrn(&e,&py))break;
    }
    printf("\x1b[2J\x1b[;H");
    printf("the information of the game:\n");
    printf("    delay:%.2fms\n    min-number:%d\n",((double)(speed_now*PROD_TIME))/1000,min);
    printf("    max-number:%d\n    the score of one expression:%d\n",max,score_now);
    printf("score:%d  fast:%.2g  counts:%d  correct percent: %.2g\n",py.score, py.fast,py.count,py.corr_perc);

return 0;
}

