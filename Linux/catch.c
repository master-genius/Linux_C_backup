#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define Y_ST        0
#define Y_END       23
#define X_ST        0
#define X_END       47

#define UP          1
#define DOWN        2
#define LEFT        4
#define RIGHT       8

#define QUIT        4

#define SPEED       204800

#define SPEED_MAX   25600

#define CUR_MAX     5

#define CUR_INI     3

#define SCORE_ONE   7

#define LEVEL_UP    128


#define ERR_MAX     143

struct ch_list
{
    char wh;
    char direc;
    int pos_y;
    int pos_x;
    int speed;
    int score;
    struct ch_list* next;
    struct ch_list* prev;
};

struct ch_ctl
{
    struct ch_list* head;
    //struct ch_list* end;

    unsigned int speed;
    unsigned int curct;
    unsigned int total;
    unsigned int cur_max;
    unsigned int err_count;
    unsigned int got_score;
    unsigned int got_count;
};


int init_scrn();

int init_chctl(struct ch_ctl*);

int get_judge(struct ch_ctl*, char);

int prod_ch(struct ch_ctl*, int);

int update(struct ch_ctl*);

int rm_ch(struct ch_ctl*, struct ch_list*);

void destroy_chlist(struct ch_ctl*);

int out_scrn(struct ch_ctl*);

int main()
{
    struct ch_ctl cc;

    if(init_scrn()==-1)return -1;

    if(init_chctl(&cc)==-1)return -1;

    out_scrn(&cc);

    unsigned int seed=0;

    char g=0;


    while(1)
    {
        usleep(cc.speed);

        g=getch();

        if(g>0)
        {
            if(g==QUIT)break;
            else if(g>='a' && g<='z')
                if(get_judge(&cc,g)==-1)break;
        }

        if(cc.err_count >= ERR_MAX)
        {
            clear();
            move(3,7);
            printw("YOU LOSE!");
            refresh();
            sleep(1);
            break;
        }
        if(cc.curct < cc.cur_max)
            if(prod_ch(&cc,seed)==-1)break;
            else seed++;
        if(out_scrn(&cc)==-1)break;
        if(update(&cc)==-1)break;
        if((cc.got_count%LEVEL_UP)==0 && cc.got_count>0)
            if(cc.cur_max<CUR_MAX){cc.cur_max++;cc.err_count=0;}
        clear();
    }

    destroy_chlist(&cc);
    endwin();

return 0;
}


int init_scrn()
{
    if(initscr()==NULL)return -1;
    raw();
    nodelay(stdscr,TRUE);

return 0;
}

int init_chctl(struct ch_ctl*cc)
{
    if(!cc)return -1;

    cc->head=(struct ch_list*)malloc(sizeof(struct ch_list));

    if(!cc->head)
    {
        perror("malloc");
        return -1;
    }

    cc->head->next = cc->head->prev = NULL;

    //cc->end=NULL;

    cc->got_score = 0;
    cc->got_count = 0;
    cc->speed = SPEED;
    cc->total = 0;
    cc->curct=0;
    cc->cur_max=CUR_INI;
    cc->err_count=0;

    int i;
    for(i=0;i<CUR_INI;i++)
    {
        if(prod_ch(cc,i)==-1)
        {
            destroy_chlist(cc);
            return -1;
        }
    }

return 0;
}

int get_judge(struct ch_ctl*cc, char w)
{
    if(!cc || !cc->head)return -1;

    struct ch_list* p=NULL;

    int right=0;

    for(p=cc->head->next;p!=NULL;p=p->next)
    {
        if(p->wh==w)
        {
            cc->got_count++;
            cc->got_score += p->score;
            right=1;
            if(rm_ch(cc,p)==-1)return -1;
            break;
        }
    }
    if(right==0)cc->err_count++;

return 0;
}

int prod_ch(struct ch_ctl*cc, int seed)
{
    if(!cc || !cc->head)return -1;

    if(cc->curct >= cc->cur_max)return 0;

    struct ch_list* p = (struct ch_list*)malloc(sizeof(struct ch_list));

    if(!p)
    {
        perror("malloc");
        return -1;
    }

    srand(seed+time(0));
    p->wh = (rand()%26)+97;

    if(p->wh > 'z' || p->wh < 'a')
        p->wh = 'b';

    p->score = SCORE_ONE;

    srand(seed+1);
    p->pos_y = (rand()%(Y_END-Y_ST-1))+Y_ST+1;

    srand(seed+2);
    p->pos_x = (rand()%(X_END-X_ST-1))+X_ST+1;

    srand(seed+3);

    int dire = (rand()%4);

    if(dire<0 || dire>=4)dire=0;

    dire = 1<<dire;

    p->direc = dire;

    switch(p->direc)
    {
        case UP:
        {
            p->pos_y = Y_END-1;
        }break;

        case DOWN:
        {
            p->pos_y = Y_ST+1;
        }break;

        case LEFT:
        {
            p->pos_x = X_END-1;
        }break;

        case RIGHT:
        {
            p->pos_x = X_ST+1;
        }break;

        default:
        {
            p->pos_y = Y_END-1;
            p->direc = UP;
        }
    }

    p->score = SCORE_ONE;

    struct ch_list* q = NULL;

    q=cc->head->next;
    cc->head->next = p;
    p->prev = cc->head;
    p->next = q;
    if(q)q->prev = p;
    //p=q=NULL;

    cc->total++;
    cc->curct++;

return 0;
}

int update(struct ch_ctl* cc)
{
    if(!cc || !cc->head)return -1;

    struct ch_list* p=NULL;

    for(p=cc->head->next;p!=NULL; p=p->next)
    {
        switch(p->direc)
        {
            case UP:
            {
                p->pos_y -= 1;
            }break;

            case DOWN:
            {
                p->pos_y +=1;
            }break;

            case LEFT:
            {
                p->pos_x -= 2;
            }break;

            case RIGHT:
            {
                p->pos_x += 2;
            }break;

            default:
                p->pos_x=X_ST;

        }
        if(p->pos_y <= Y_ST || p->pos_y >= Y_END || p->pos_x <= X_ST || p->pos_x >= X_END)
            if(rm_ch(cc,p)==-1)
                return -1;
    }

return 0;
}

int rm_ch(struct ch_ctl*cc, struct ch_list*p)
{
    if(!cc || !cc->head || !p)return -1;

    struct ch_list* q = NULL,*b=NULL;

    q = p->next;
    b = p->prev;

    if(q)q->prev = b;
    if(b)b->next = q;

    free(p);
    p=NULL;

    cc->curct--;

return 0;
}


int out_scrn(struct ch_ctl* cc)
{
    if(!cc || !cc->head)return -1;

    int i;

    for(i=X_ST;i<=X_END;i++)
    {
        mvaddch(Y_ST,i,'-');
        mvaddch(Y_END,i,'-');
    }

    for(i=Y_ST;i<=Y_END;i++)
    {
        mvaddch(i,X_ST,'|');
        mvaddch(i,X_END,'|');
    }

    struct ch_list* p=NULL;

    for(p=cc->head->next;p!=NULL;p=p->next)
        mvaddch(p->pos_y,p->pos_x,p->wh);

    mvaddstr(Y_ST,X_END+2,"score: ");
    move(Y_ST,X_END+2+7);
    printw("%d",cc->got_score);

    mvaddstr(Y_ST+2,X_END+2,"counts: ");
    move(Y_ST+2,X_END+2+8);
    printw("%d",cc->got_count);

    mvaddstr(Y_ST+4,X_END+2,"erroneous counts: ");
    move(Y_ST+4,X_END+2+18);
    printw("%d",cc->err_count);

    mvaddch(Y_END+2,X_ST+1,'_');

    refresh();

return 0;
}

void destroy_chlist(struct ch_ctl*cc)
{
    if(!cc || !cc->head)return ;

    struct ch_list*p,*q;

    p = q = cc->head;

    while(p)
    {
        q=q->next;
        free(p);
        p=q;
    }
    p=q=NULL;
    cc->head=NULL;
}
