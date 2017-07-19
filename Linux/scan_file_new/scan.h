#ifndef SCAN_H
#define SCAN_H

#include	"read_def.h"

struct fary
{
	char line[CHAR_MAX+3];
	int slen;
	struct fary*next;
};


int scan_file(char*);

int get_inst(char cmd, struct file_curinf*, struct fary**);

int out_scrn(struct file_curinf*, struct fary**);

void out_err(int er);

void destroy_pages(struct fary*);

void scan_help();

#endif
