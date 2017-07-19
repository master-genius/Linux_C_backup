#include <ncurses.h>


char get_flag;

#define RESULT_MAX  32

char res[RESULT_MAX+1];

int quit;

int get_in();

int main()
{
    quit=0;
    get_flag=0;

    initscr();
    raw();
    nodelay(stdscr,TRUE);

    get_in();

    endwin();

return 0;
}

int get_in()
{

    int i=0;
    char c;

    while(!quit)
    {
        c=getch();
        if(c>0 && i< RESULT_MAX && i>=0)
        {
            if(c=='\n')
            {
                //r[i]=0;
                get_flag=1;
                if(strncmp(res,"q",1)==0)quit=1;
            }
            else if(c==8 || c==127)
            {
                if(i>0){i--;res[i]=0;}
            }
            else if((c>='0' && c<='9')||c=='.' || c=='q')
            {
                res[i]=c;i++;
                res[i]=0;
            }
        }
        mvaddstr(0,0,res);
        refresh();
        usleep(51200);
        clear();
    }

return 0;
}
