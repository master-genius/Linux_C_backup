#include <stdio.h>
#include <string.h>
#include "sdef.h"


int creat_scrn(struct scr_info* sci)
{
    if(!sci)return -1;

    int i,j;

    for(i=0;i<AREA_X;i++)
    {
        sci->scr[0][i]='_';
        sci->scr[AREA_Y][i]='*';
        sci->sflag[0][i] = SCR_WALL;
        sci->sflag[AREA_Y][i] = SCR_WALL;
    }

    for(i=1;i<AREA_Y;i++)
    {
        sci->scr[i][0] = '|';
        sci->scr[i][AREA_X-1] = '|';
        sci->sflag[i][0] = SCR_WALL;
        sci->sflag[i][AREA_X-1] = SCR_WALL;
    }

    for(i=0;i<=AREA_Y;i++)
        sci->scr[i][AREA_X] = 0;

    for(i=1;i<AREA_Y;i++)
        for(j=1;j<AREA_X-1;j++)
        {
            sci->scr[i][j] = ' ';
            sci->sflag[i][j] = SCR_UNUS;
        }

    return 0; 
}

int simple(struct scr_info* sci)
{
    if(!sci)
        return -1;

    int i;

    for(i=4;i<11;i++)
    {
        sci->scr[i][14]='|';
        sci->scr[i][27]='|';
        sci->sflag[i][14]=SCR_WALL;
        sci->sflag[i][27]=SCR_WALL;
    }

    for(i=14;i<28;i++)
    {
        sci->scr[13][i]='%';
        sci->sflag[13][i]=SCR_WALL;
    }

    return 0;
}

int hard(struct scr_info* sci)
{
    if(!sci)return -1;

    int i;

    for(i=12;i<23;i++)
    {
        sci->scr[3][i] = ':';
        sci->scr[13][i+10] = ':';
        sci->sflag[3][i]=SCR_WALL;
        sci->sflag[13][i+10]=SCR_WALL;
    }

    for(i=3;i<8;i++)
    {
        sci->scr[i][32] = '|';
        sci->scr[i+6][12] = '|';
        sci->sflag[i][32] = SCR_WALL;
        sci->sflag[i+6][12] = SCR_WALL;
    }

    for(i=12;i<33;i++)
    {
        sci->scr[8][i] = ':';
        sci->sflag[8][i] = SCR_WALL;
    }

    for(i=4;i<13;i++)
    {
        sci->scr[i][22] = '|';
        sci->sflag[i][22] = SCR_WALL;
    }

    return 0;
}

int fuck(struct scr_info* sci)
{
    if(!sci) return -1;

    int i;

    for(i=6;i<37;i++)
    {
        sci->scr[3][i] = '#';
        sci->sflag[3][i] = SCR_WALL;
        sci->scr[14][i] = '#';
        sci->sflag[14][i] = SCR_WALL;
    }

    for(i=6;i<12;i++)
    {
        sci->scr[6][i] = ':';
        sci->sflag[6][i] = SCR_WALL;
    }

    for(i=7;i<11;i++)
    {
        sci->scr[i][6] = '|';
        sci->sflag[i][6] = SCR_WALL;
    }

    for(i=7;i<9;i++)
    {
        sci->scr[8][i] = ':';
        sci->sflag[8][i] = SCR_WALL;
    }
 
    for(i=7;i<10;i++)
    {
        sci->scr[i][16] = '$';
        sci->scr[i][21] = '$';
        sci->sflag[i][16] = SCR_WALL;
        sci->sflag[i][21] = SCR_WALL;
    }

    sci->scr[10][17] = '\\';
    sci->sflag[10][17] = SCR_WALL;
    sci->scr[10][20] = '/';
    sci->sflag[10][20] = SCR_WALL;
    
    for(i=18;i<20;i++)
    {
        sci->scr[10][i] = ':';
        sci->sflag[10][i] = SCR_WALL;
    }

    for(i=27;i<30;i++)
    {
        sci->scr[7][i] = '&';
        sci->scr[10][i] = '&';
        sci->sflag[7][i] = SCR_WALL;
        sci->sflag[10][i] = SCR_WALL;
    }

    sci->scr[8][26] = '/';
    sci->scr[9][26] = '\\';
    sci->sflag[8][26] = SCR_WALL;
    sci->sflag[9][26] = SCR_WALL;

    for(i=6;i<11;i++)
    {
        sci->scr[i][34] = '|';
        sci->sflag[i][34] = SCR_WALL;
    }

    sci->scr[8][35] = '/';
    sci->sflag[8][35] = '\\';

    int j;
    for(i=9,j=35;i<11;i++,j++)
    {
        sci->scr[i][j] = '\\';
        sci->sflag[i][j] = SCR_WALL;
    }

    return 0;
}


