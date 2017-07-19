#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "sdef.h"
#include <unistd.h>
#include <fcntl.h>

int init_info(struct snk_info*si, struct scr_info*sci)
{
    if(!si || !sci)return ERR_EMPT;
    
    si->blen = INIT_LEN;
    si->speed = SPEED_DEF;
    si->head = HEAD;
    si->body = BODY;
    
    int end = si->blen;
    int i;
    for(i=end-1;i>=0;i--)
    {
        si->sp[i].px = INIT_X;
        si->sp[i].py = INIT_Y+1;
    }

    if(creat_scrn(sci))return -1;

    for(i=0;i<end;i++)
    {
        sci->scr[si->sp[i].py][si->sp[i].px] = BODY; 
        sci->sflag[si->sp[i].py][si->sp[i].px] = SCR_SNAK;
    }
    sci->scr[si->sp[0].py][si->sp[0].px] = HEAD;
    sci->sflag[si->sp[0].py][si->sp[0].px] = SCR_SNAK;
    sci->scr[FOOD_IY][FOOD_IX] = FOOD;
    sci->sflag[FOOD_IY][FOOD_IX] = SCR_FOOD;

    head_y = si->sp[0].py;
    head_x = si->sp[0].px;

    last_y = si->sp[end-1].py;
    last_x = si->sp[end-1].px;

return 0;
}

int get_mode(struct scr_info* sci, int flag)
{
    if(!sci)return -1;

    switch(flag)
    {
        case MODE_SIMPL:
        {
            simple(sci);
            self_flag = 1;
        }break;

        case MODE_HARD:
        {
            hard(sci);
            self_flag = 0;
        }break;

        case MODE_FUCK:
        {
            fuck(sci);
            self_flag = 0;
        }break;

        default:
            printf("There is no this mode. Setting to default\n");
    }

    return 0;
}

int upd_info(struct snk_info*si, struct scr_info*sci)
{
    if(!si || !sci) return -1;

    if(move_to == PASUE)return 0;

    int i;
    last_y = si->sp[si->blen-1].py;
    last_x = si->sp[si->blen-1].px;
    for(i=si->blen-1;i>=1;i--)
    {
        si->sp[i].py = si->sp[i-1].py;
        si->sp[i].px = si->sp[i-1].px;
    }

    switch(move_to)
    {
        case UP:
        {
            si->sp[0].py -= 1;
        }break;

        case DOWN:
        {
            si->sp[0].py += 1;
        }break;

        case LEFT:
        {
            si->sp[0].px -= 1;
        }break;

        case RIGHT:
        {
            si->sp[0].px += 1;
        }break;

        default:;
    }

    for(i=1;i<si->blen;i++)
    {
        sci->scr[si->sp[i].py][si->sp[i].px] = BODY;
        sci->sflag[si->sp[i].py][si->sp[i].px] = SCR_SNAK;
    }

    sci->scr[si->sp[0].py][si->sp[0].px] = HEAD;
    sflag_buf = sci->sflag[si->sp[0].py][si->sp[0].px];
    sci->sflag[si->sp[0].py][si->sp[0].px] = SCR_SNAK;

    sci->scr[last_y][last_x] = ' ';
    sci->sflag[last_y][last_x] = SCR_UNUS;

    if(si->sp[0].py <=0 || si->sp[0].py >= AREA_Y)
    {
        snake_state = ST_DEAD;
        return 0;
    }

    if(si->sp[0].px <= 0 || si->sp[0].px >= AREA_X)
    {
        snake_state = ST_DEAD;
        return 0;
    }

    switch(sflag_buf)
    {
        case SCR_UNUS:
        {
        }break;

        case SCR_SNAK:
        {
            if(self_flag)
                snake_state = ST_DEAD;
        }break;

        case SCR_FOOD:
        {
            si->score += FOOD_SCORE;
            sci->scr[last_y][last_x] = BODY;
            sci->sflag[last_y][last_x] = SCR_SNAK;
            si->food_count++;
            si->blen++;
            si->sp[si->blen-1].py = last_y;
            si->sp[si->blen-1].px = last_x;
            if(prod_fdpz(sci,WHAT_FOOD))return -1;
            if(si->food_count == PRIZE_COUNT)
                return prod_fdpz(sci,WHAT_PRIZ);
        }break;

        case SCR_PRIZ:
        {
            si->score += PRIZ_SCORE;
            si->blen += 1;
            si->priz_count++;
            si->food_count=0;
            priz_st = 0;
            si->sp[si->blen-1].py = last_y;
            si->sp[si->blen-1].px = last_x;
            sci->scr[last_y][last_x] = BODY;
            sci->sflag[last_y][last_x] = SCR_SNAK;
            si->blen++;
            if(sci->scr[last_y][last_x-1] == ' ')
                last_x--;
            else if(sci->scr[last_y][last_x+1] == ' ')
                last_x++;
            else if(sci->scr[last_y-1][last_x] == ' ')
                last_y--;
            else if(sci->scr[last_y+1][last_x] == ' ')
                last_y++;
            sci->scr[last_y][last_x] = BODY;
            si->sp[si->blen-1].py = last_y;
            si->sp[si->blen-1].px = last_x;
            sci->sflag[last_y][last_x] = SCR_SNAK;
        }break;

        case SCR_WALL:
        {
            //sci->scr[si->sp[0].py][si->sp[0].px] = HEAD;
            snake_state = ST_DEAD;
            return 0;
        }break;

        default:;
    }

    if(priz_st)
    {
        priz_st--;
        if(priz_st==0)
        {
            sci->scr[pz_y][pz_x] = ' ';
            sci->sflag[pz_y][pz_x] = SCR_UNUS;
            si->food_count = 0;
        }
    }

    return 0;
}

int out_info(struct snk_info* si, struct scr_info* sci)
{
    if(!si || !sci)return -1;

    int i=0,j=0;
    
    for(i=0;i<=AREA_Y;i++)
        printf("%s\n",sci->scr[i]);

    printf("score: %d  %d,%d\n",si->score,si->sp[0].py,si->sp[0].px);
    printf("len:%d\n",si->blen);

    return 0;
}

int prod_fdpz(struct scr_info* sci, int what)
{
    if(!sci)return -1;

    int i,j;
    int count=0;

    int uns[(AREA_Y-1)*(AREA_X-1)];
    for(i=1;i<AREA_Y-1;i++)
        for(j=1;j<AREA_X-1;j++)
        {
            if(sci->sflag[i][j] == SCR_UNUS)
                uns[count++] = i*100+j;
        }
    srand(time(0));
    int k = rand();
    srand(k);
    k = rand()%count;

    i=uns[k]/100;
    j=uns[k]%100;
    switch(what)
    {
        case WHAT_FOOD:
        {
            sci->scr[i][j] = FOOD;
            sci->sflag[i][j] = SCR_FOOD;
        }break;

        case WHAT_PRIZ:
        {
            sci->scr[i][j] = PRIZE;
            sci->sflag[i][j] = SCR_PRIZ;
            pz_y = i;
            pz_x = j;
            priz_st = PRIZ_TIME;
        }break;

        default:;
    }

    return 0;
}

int set_imode(struct termios* stty, int mode)
{
    if(mode==START_MODE)
    {
        if(tcgetattr(0,stty)==-1)
        {
            printf("error to get tty setting\n");
            return -1;
        }
        stty->c_lflag&=~ICANON;
        stty->c_lflag&=~ECHO;
        if(tcsetattr(0,TCSANOW,stty)==-1)
        {
            printf("error to set new tty\n");
            return -1;
        }
        int fg;
        fg=fcntl(0,F_GETFL);
        fg|=O_NDELAY;
        if(fcntl(0,F_SETFL,fg))
        {
            printf("Error:set in mode\n");
            perror("fcntl");
            return -1;
        }
                        
    }
    else if(mode==END_MODE)
    {
        stty->c_lflag|=ICANON;
        stty->c_lflag|=ECHO;
        if(tcsetattr(0,TCSANOW,stty)==-1)
        {
            printf("error reset default tty setting\n");
            fflush(stdout);
            return -1;
        }
        int fg;
        fg=fcntl(0,F_GETFL);
        fg &= ~O_NDELAY;
        if(fcntl(0,F_SETFL,fg))
        {
            printf("Error:set in mode\n");
            perror("fcntl");
            return -1;
        }
    }

    return 0;
}

int game_start()
{
    struct scr_info sci;
    struct snk_info si;
    struct termios stty;

    snake_state = -1;
    sflag_buf = -1;
    priz_st = 0;
    move_to = DOWN;
    self_flag = 1;

    if(init_info(&si,&sci))return -1;

    printf("enter mode:1.[simple] 2.[basic] 3.[hard] 4.[fuck]__");
    int level=0;
    
    level = getchar();
    level -= 48;
    if(get_mode(&sci,level))return -1;
    if(set_imode(&stty, START_MODE))return -1;

    char inst=0;
    while(1)
    {
        inst = getchar();

        if(inst == '+' && (si.speed > SPEED_MAX))
            si.speed -= TIMER;
        else if(inst == '-' && (si.speed < SPEED_MIN))
            si.speed += TIMER;
        else if(inst == QUIT)
            break;
        else if(inst == ' ')
            move_to = PASUE;
        else if(strchr(INST_STR,inst))
        {
            if(inst != move_to && self_flag==0)
                switch(inst)
                {
                    case UP:
                        move_to = UP;
                        break;
                    case DOWN:
                        move_to = DOWN;
                        break;
                    case LEFT:
                        move_to = LEFT;
                        break;
                    case RIGHT:
                        move_to = RIGHT;
                        break;
                    default:;
                }
            else if(inst != move_to && self_flag==1)
                switch(inst)
                {
                    case UP:
                        if(move_to != DOWN)
                            move_to = UP;
                        break;
                    case DOWN:
                        if(move_to != UP)
                            move_to = DOWN;
                        break;
                    case LEFT:
                        if(move_to != RIGHT)
                            move_to = LEFT;
                        break;
                    case RIGHT:
                        if(move_to != LEFT)
                            move_to = RIGHT;
                        break;
                    default:;
                }
        }

        printf("\x1b[2J\x1b[;H");
        if(upd_info(&si,&sci))break;
        if(out_info(&si,&sci))break;
        usleep(si.speed);
        
        if(si.blen >= BODY_MLEN)
        {
            printf("You win!\n");
            break;
        }
        if(snake_state == ST_DEAD)
            break;


    }
    
    if(snake_state == ST_DEAD)
        printf("GAME OVER!\n");

    if(set_imode(&stty, END_MODE))return -1;
return 0;
}

