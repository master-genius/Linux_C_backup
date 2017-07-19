#include	<stdio.h>
#include	<sys/stat.h>
#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"read_def.h"
#include	"scan.h"

int scan_file(char*path)
{
    if(!path)
    {
    	out_err(ER_BDPTR);
    	return -1;
    }

    FILE*fd=fopen(path,"r");
    if(fd==NULL)
    {
       perror("fopen");
       return -1;
    }

    char cmd=0;
    int lines=0;
    struct fary* cur=NULL;
    struct fary* p=NULL;
    
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    
    int len=0;
    while(!feof(fd))
    {
		p=(struct fary*)malloc(sizeof(struct fary));
		if(!p)
		{
			destroy_pages(cur);
			out_err(ER_MEM);
			return -1;
		}
		memset(p->line,0,CHAR_MAX);
		p->next=cur;
		cur=p;
		fgets(cur->line,CHAR_MAX,fd);
	
		len=strlen(cur->line);
		if(cur->line[len-1]!='\n')
		{
			cur->line[len++]='\n';
			cur->line[len]=0;
		}
		cur->slen=len;
		lines++;
	
    }fclose(fd);
    
    struct file_curinf fci;
    
    fci.ln_max=lines;
    fci.ln_cur=0;
    fci.page=SCRNLN;
    fci.quit=0;
    fci.tab=1;
    
    struct fary*lptr[lines];
    
    for(int i=0;i<lines;i++)
		lptr[i]=NULL;
    
    int i=0;
    for(i=lines-1,p=cur;p!=NULL;p=p->next,i--)
		lptr[i]=p;
    
    if(out_scrn(&fci,lptr)==-1) return -1;
    
    while(1)
    {
		cmd=getchar();
		if(get_inst(cmd, &fci, lptr)==-1)
			break;
		if(fci.quit==1)
		{
			printf("\x1b[2J\x1b[;H");
			break;
		}
		if(out_scrn(&fci,lptr)==-1) return -1;
    }

    destroy_pages(cur);
return 0;
}

int get_inst(char cmd, struct file_curinf*fci, struct fary**p)
{
	if(!fci || !p)
	{
		out_err(ER_BDPTR);
		return -1;
	}
	switch(cmd)
	{
		case PAGEUP:
			fci->ln_cur=(fci->ln_cur > fci->page)?(fci->ln_cur - fci->page):0;
			return 0;
			
		case PAGEDOWN:
			if(fci->ln_max > fci->page)
			{
				if((fci->ln_cur + fci->page) > fci->ln_max-1)
					return 0;
				else
					fci->ln_cur = fci->ln_cur + fci->page;

				if((fci->ln_cur + fci->page) > fci->ln_max-1)
					fci->ln_cur = fci->ln_max - fci->page;

			}
			return 0;

		case PRIVLN:
			if(fci->ln_cur > 0)
			{
				fci->ln_cur -= 1;
			}
			return 0;
		
		case NEXTLN:
			if(fci->ln_cur<fci->ln_max-1)
			{
				if((fci->ln_cur + fci->page) >= fci->ln_max)
					return 0;
				else
					fci->ln_cur += 1;
				if(out_scrn(fci,p)==-1) return -1;
			}
			return 0;

		case ADDPG:
			if(fci->page < SCRNMAX)
			{
				fci->page++;
				if(fci->ln_cur > 0) fci->ln_cur -= 1;
				if(out_scrn(fci,p)==-1) return -1;

			}
			return 0;

		case MISPG:
			if(fci->page > SCRNMIN)
			{
				fci->page -= 1;
			}
			return 0;

		case QUIT:
			fci->quit = 1;
			return 0;

		case TABTSP:
			fci->tab = 0;
			return 0;

		case OPTAB:
			fci->tab = 1;
			if(out_scrn(fci,p)== -1)
				return -1;
			return 0;

		case HELP:
			scan_help();
			return 0;

		default: return 0;

	}
return 0;
}

int out_scrn(struct file_curinf*fci, struct fary**p)
{
	if(!fci || !p)
	{
		out_err(ER_BDPTR);
		return -1;
	}
	printf("\x1b[2J\x1b[;H");
	fflush(stdout);

	for(int i=0;i < fci->page && fci->ln_cur < (fci->ln_max - i);i++)
		if(p[fci->ln_cur+i])
		{
			if(fci->tab == 1)
				printf("%s",p[fci->ln_cur+i]->line);
			else
			{
				for(int k=0;k < p[fci->ln_cur+i]->slen; k++)
					if(p[fci->ln_cur+i]->line[k]==9)
						printf("    ");
					else
						printf("%c",p[fci->ln_cur+i]->line[k]);

			}
		}
		else
		{
			out_err(ER_BDPTR);
			return -1;
		}
	printf("-BruceWang--TOTAL LINES: %d CURRENT LINE: %d %s",fci->ln_max,fci->ln_cur,WAIT);
return 0;
}

void out_err(int er)
{
	switch(er)
	{
		case ER_MEM:
			printf("can not get memory\n");
			return ;

		case ER_FSTAT:
			printf("can not get the stat of the file\n");
			return ;

		case ER_BDPTR:
			printf("error:bad pointer\n");
			return ;

		default: return ;
	}
}

void destroy_pages(struct fary*cur)
{
	struct fary*p=cur;

	while(p)
	{
		cur=cur->next;
		free(p);
		p=cur;
	}
}

void scan_help()
{
	char help=0;
	printf("\x1b[2J\x1b[;H");
	printf("this program just can scan common files\n");
	printf("	p: previous line\n");
	printf("	n: next line\n");
	printf("	u: pageup\n");
	printf("	d: pagedown\n");
	printf("	t: tab to space\n");
	printf("	a: add the page's size\n");
	printf("	m: minus the page's size\n");
	printf("	b: open the tab\n");
	printf("	h: help\n");
	printf("	q: quit\n");
	fflush(stdout);
	printf("enter any key to back..");
	help=getchar();
}
