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
#define ZERO    "0"
#define ONE     "1"


#define PREC_DEF    11
#define PREC_MIN    0
#define PREC_MAX    1024

#define BITS_MAX    16384

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


#endif
