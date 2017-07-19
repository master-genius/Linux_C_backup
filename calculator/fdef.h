#ifndef FDEF_H
#define FDEF_H

#include "ddef.h"


int bw_add(struct number*, struct number*, struct number*);

int bw_mis(struct number*, struct number*, struct number*);

int bw_mul(struct number*, struct number*, struct number*);

int bw_div(struct number*, struct number*, struct number*);

int bw_pow(struct number*, struct number*, struct number*);

int bw_ln(struct number*, struct number*, struct number*);

int bw_lg(struct number*, struct number*, struct number*);

/*basic operation*/

int nm_copy(struct number*, struct number*);

int nm_cut(struct number*, struct number*);

int nm_comp(struct number*, struct number*);

int nm_free(struct number*);

int nm_out(struct number*);

int chadd(struct number*, struct number*, struct number*);

int chmis(struct number*, struct number*, struct number*);

int chmul(struct number*, struct number*, struct number*);

int chdiv(struct number*, struct number*, struct number*);

int mvbit(struct number*, int, int);

int crnm(struct number*, char*);

int bit_mul(struct number*, char, struct number*);

int bitsm(struct number*, struct number*);

/********/

#endif
