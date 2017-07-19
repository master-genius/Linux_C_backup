#ifndef READ_DEF_H
#define READ_DEF_H

#define SCRNLN		30
#define SCRNMAX		64
#define SCRNMIN		2

#define LCHAR_MAX	128
#define CHAR_MAX	LCHAR_MAX+1
#define START_MODE	0
#define END_MODE	1
#define WAIT		"---MORE---_>"
#define PAGEUP		'u'
#define PAGEDOWN	'd'
#define PRIVLN		'p'
#define NEXTLN		'n'
#define QUIT		'q'
#define ADDPG		'a'
#define MISPG		'm'
#define TABTSP		't'
#define OPTAB		'b'
#define HELP		'h'

#define ER_BDPTR	1
#define ER_MEM		2
#define ER_FSTAT	3


struct file_curinf
{
	int ln_max;
	int ln_cur;
	int page;
	int tab;
	int quit;
};

#endif
