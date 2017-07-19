#ifndef DDEF_H
#define DDEF_H

/*start define*/

#define END_CH      -1

#define POW_MAX     "99999999"
#define POW_MBS     8

#define ERR_EMPT        1 //empty pointer
#define ERR_OPOW        2 //pow too long
#define ERR_OVERFLOW    3
#define ERR_COMNM       4 //complex error
#define ERR_NBIT        5 // now I don't what it is
#define ERR_NMTL        6 // number too long
#define ERR_UNPN        7 //unknow pn_flag;
#define ERR_DIVZ        8
/**********************/

#define MORE    1
#define EQUAL   2
#define LESS    3
#define ERROR   -1

#define EN      "2.718281828"
#define PI      "3.141592653"

#define PREC_DEF    9
#define PREC_MIN    0
#define PREC_MAX    1024

#define BITS_MAX    11111111

struct number
{
    char* nm;
    char pn_flag;
    unsigned int ppl;
    unsigned int ppr;
    unsigned int bits;
    unsigned int end;
};

struct number nm_buf_a;
struct number nm_buf_b;
struct number nm_buf_c;

struct number e;
struct number pi;
struct number zero;
struct number one;

char* add_buf;
char* mul_buf;
char* div_buf;
int err_num;
int prec;

static char ntable[9][9]={\
                {1,2,3,4,5,6,7,8,9},\
                {2,4,6,8,10,12,14,16,18},\
                {3,6,9,12,15,18,21,24,27},\
                {4,8,12,16,20,24,28,32,36},\
                {5,10,15,20,25,30,35,40,45},\
                {6,12,18,24,30,36,42,48,54},\
                {7,14,21,28,35,42,49,56,63},\
                {8,16,24,32,40,48,56,64,72},\
                {9,18,27,36,45,54,63,72,81}\
            };

#endif
