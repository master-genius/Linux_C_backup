#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#define MAT_ERR		-1
#define NONE		-2
#define BW_DIR		1
#define BW_FILE		2
#define BW_UNK		3
#define MD_LINE		1
#define MD_BLK		2
#define LINE_MAX	512

struct redir
{
	char*fname;
	char flag;
	struct redir* next;
};


int mat(char*src, char*text, char*mv, int src_len);
int recur_dir(char*path,struct redir*rd);
void destroy(struct redir* rd);
int bw_match(char*src,struct redir* rd);
int matloop(char*src,char*fname, char*mv);
int cal_mvlen(char*src, char*mv);

int main(int ac, char* av[])
{
	if(ac<3)
	{
		printf("error:less arguments---str---path\n");
		return -1;
	}
	
	struct redir* rd=NULL;
	struct redir* p=NULL;
	struct redir* q=NULL;
	struct stat st;
	
	int i;
	for(i=2;i<ac;i++)
	{
		if(stat(av[i],&st))continue;
		
		p=(struct redir*)malloc(sizeof(struct redir));
		if(!p)
		{
			destroy(q);
			perror("malloc");
			return -1;
		}
		if((st.st_mode&S_IFDIR)==S_IFDIR)p->flag=BW_DIR;
		else if((st.st_mode&S_IFREG)==S_IFREG)p->flag=BW_FILE;
		else
		{
			free(p);
			continue;
		}
		p->fname=(char*)malloc(sizeof(char)*(strlen(av[i])+2));
		if(!p->fname)
		{
			free(p);
			p=NULL;
			destroy(q);
			perror("malloc");
			return -1;
		}
		strcpy(p->fname,av[i]);
		p->next=q;
		q=p;
	}
	rd=q;
	p=q=NULL;
	
	if(bw_match(av[1],rd))
		return -1;
	
return 0;
}

int bw_match(char*src, struct redir* rd)
{
	if(!src || !rd)return MAT_ERR;
	
	struct redir* p=rd;
	char mv[256];
	if(cal_mvlen(src,mv))
	{
		destroy(rd);
		return -1;
	}
	
	while(p)
	{
		if(p->flag==BW_FILE)
			matloop(src,p->fname, mv);
		else if(p->flag==BW_DIR)
			if(recur_dir(p->fname, p))
			{
				destroy(rd);
				return -1;
			}
		p=p->next;
		free(rd);
		rd=p;
	}
	destroy(rd);
	
return 0;
}

int cal_mvlen(char*src, char*mv)
{
	if(!src || !mv)return -1;
	
	int mlen=strlen(src);
	int i;
    for(i=0;i<256;i++)
        mv[i]=mlen;
	int n;
	int bk;
    for(n=0; n < mlen; n++)
	{
		bk=mv[(int)(src[n])];
        mv[(int)(src[n])]=mlen-n-1;
		if(mv[(int)(src[n])]<=0)mv[(int)(src[n])]=bk;
		if(mv[(int)(src[n])]<=0)mv[(int)(src[n])]=mlen;
	}

return 0;	
}

int matloop(char*src,char*fname, char*mv)
{
	if(!src || !fname || !mv)return -1;
	
	char line[LINE_MAX+1];
	FILE* f=NULL;
	
	f=fopen(fname, "r");
	if(!f)
	{
		perror("fopen");
		return -1;
	}
	int lin=0;
	int first=0;
	int sl=strlen(src);
	int i;
	int index;
	char*p=NULL;
	while(!feof(f))
	{
		p=fgets(line, LINE_MAX,f);
		if(!p && !feof(f))
			return -1;
		lin++;
		//printf("start:  %s",line);
		if((index=mat(src,line, mv, sl))>0)
		{
			if(first==0)
			{
				printf("\x1b[1;35;40m");
				printf("%s:\n",fname);
				printf("\x1b[0;;m");
				first=1;
			}
			printf("	%d:",lin);
			for(i=0;line[i]!=0;i++)
			{
				if(i==index)
					printf("\x1b[1;36;40m");
				else if((i-index)>=sl)
					printf("\x1b[0;;m");
				printf("%c",line[i]);
			}if(line[i-1]!='\n')printf("\n");
			fflush(stdout);
		}
	}fclose(f);
	printf("\x1b[0;;m");
	if(first>0)
		printf("\n");
	
return 0;
}

int mat(char*src, char*text, char*mv, int src_len)
{
    if(!src || !text || src_len<=0 || !mv)return MAT_ERR;

    int tlen=strlen(text);

    if(src_len>tlen)return MAT_ERR;

    int a;
    int b;
    a=b=src_len-1;
    while(a>=0 && b<tlen)
    {
        if(src[a]!=text[b] && (src[a]-text[b]!=32) && (src[a]-text[b]!=-32))
        {
			//printf("%c in %d != %c in %d\n",src[a],a,text[b],b);
			if(text[b]>=0 && text[b]<256)
			{
				if((src_len-a-1)>=mv[(int)(text[b])])
					b+=src_len-a;
				else
					b+=mv[(int)(text[b])];
			}
			else
				b+=src_len;
			if(b>=tlen)return NONE;
			//printf("now:b=%d\n",b);
			a=src_len-1;
            continue;
        }
        else if(a==0)return b;
        a--;
        b--;
    }

return NONE;
}

int recur_dir(char*path,struct redir*rd)
{
	if(!path || !rd)return -1;
	
	struct redir*p=NULL,*q=NULL;
	struct stat st;
	p=rd;
	for(;p->next!=NULL;p=p->next);
	q=p;
	
	int nlen=strlen(path);
	
	char*bn=(char*)malloc(sizeof(char)*(nlen+3));
	if(!bn)
	{
		perror("malloc");
		return -1;
	}
	strcpy(bn,path);
	if(bn[nlen-1]!='/')
	{
		bn[nlen]='/';
		bn[nlen+1]=0;
	}nlen++;
	
	struct dirent* dir=NULL;
	DIR*d=NULL;
	
	d=opendir(path);
	if(!d)
	{
		free(bn);
		return -1;
	}
	
	dir=readdir(d);
	while(dir)
	{
		if(!strcmp(dir->d_name,"..")|| !strcmp(dir->d_name, "."))
		{
			dir=readdir(d);
			continue;
		}
		p=(struct redir*)malloc(sizeof(struct redir));
		if(!p)
		{
			free(bn);
			closedir(d);
			return -1;
		}
		p->fname=(char*)malloc(nlen+strlen(dir->d_name)+2);
		if(!p->fname)
		{
			closedir(d);
			free(bn);
			return -1;
		}
		strcpy(p->fname,bn);
		strcat(p->fname,dir->d_name);
		dir=readdir(d);
		if(stat(p->fname,&st))
		{
			free(p);
			continue;
		}
		if((st.st_mode&S_IFDIR)==S_IFDIR)p->flag=BW_DIR;
		else if((st.st_mode&S_IFREG)==S_IFREG)p->flag=BW_FILE;
		else
		{
			free(p->fname);
			free(p);
			p=NULL;
			continue;
		}
		
		q->next=p;
		q=p;
		q->next=NULL;
		
	}
	closedir(d);
	free(bn);
	bn=NULL;
	dir=NULL;
	d=NULL;
	
return 0;
}

void destroy(struct redir* rd)
{
	struct redir* p;	
	p=rd;
	while(p)
	{
		rd=rd->next;
		free(p->fname);
		free(p);
		p=rd;
	}
	p=rd=NULL;
}


