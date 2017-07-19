#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>
#include <regex.h>
#include <strings.h>
#include <errno.h>

/*
    This program list the stat of files . A file can be a directory or regular file, also can be a link file.
    -s:size -bs:bolck size -i:access -m:mode -t:time -l:links -b:blocks
    -a:list all information -c:the time of last change it -d:device
    -uid:user id -gid:group id -r:recursion directory -dl:don't list file
    -lt:list the number of file which belong a type
    -p: regular expression
*/
//#define PARAM   "-s -bs -b -i -m -l -t -a -d -rd -uid -gid -r -ig -dl -lt -jf -jd -h"

#define BLOCK_SIZE  512

#define FG_DEVID    0
#define FG_INODE    1
#define FG_MODE     2
#define FG_LINKS    3
#define FG_UID      4
#define FG_GID      5
#define FG_RDEVID   6
#define FG_SIZE     7
#define FG_BLKSZ    8
#define FG_BLKS     9
#define FG_TIME     10
#define FG_ALL      11


#define FG_EXPT     0
#define FG_IGNO     1

int err_empty_dir;
int flag_list_files;
int flag_list_type;
int just_file;
int just_dir;
char*pat;
regex_t rg[1];

struct file_list
{
    char*path;
    char*target;
    char name[256];
    unsigned char type;
    long long size;
    long long blocks;
    unsigned int err;
    struct stat st;
    struct file_list*next;
};

struct file_ctl
{
    unsigned int dir_count;
    unsigned int file_count;
    unsigned int link_count;
    unsigned int fifo_count;
    unsigned int blk_count;
    unsigned int sock_count;
    unsigned int chr_count;
    unsigned int count;
    unsigned int type;
    unsigned int total_size;
    struct file_list*fl;
};

struct path_list
{
    char*path;
    struct path_list*next;
};


struct file_ctl*
recur_dir(struct file_ctl*,char*,int);

struct file_list*
list_dir(char*path,int*);

int out_finf(struct file_list*, int);

int out_flist(struct file_ctl*,int);

void destroy_fctl(struct file_ctl*);

void destroy_list(struct file_list*);

void destroy_plist(struct path_list*);

void help();

int reg_pat(char*,regex_t*);

int main(int ac, char*av[])
{
    int flag=0;
    int recur=0;
    int ignore=0;
    char*path=NULL;
    pat=NULL;
    int hp=0;

    err_empty_dir=0;
    flag_list_files=1;
    flag_list_type=0;
    just_file=0;
    just_dir=0;

    struct path_list* pl=NULL,*p=NULL,*q=NULL;

    for(int i=1;i<ac;i++)
    {
        if(strcmp(av[i],"-d")==0)
        {
            flag+=1<<FG_DEVID;
        }
        else if(strcmp(av[i],"-rd")==0)
        {
            flag+=1<<FG_RDEVID;
        }
        else if(strcmp(av[i],"-l")==0)
        {
            flag+=1<<FG_LINKS;
        }
        else if(strcmp(av[i],"-s")==0)
        {
            flag+=1<<FG_SIZE;
        }
        else if(strcmp(av[i],"-bs")==0)
        {
            flag+=1<<FG_BLKSZ;
        }
        else if(strcmp(av[i],"-b")==0)
        {
            flag+=1<<FG_BLKS;
        }
        else if(strcmp(av[i],"-uid")==0)
        {
            flag+=1<<FG_UID;
        }
        else if(strcmp(av[i],"-gid")==0)
        {
            flag+=1<<FG_GID;
        }
        else if(strcmp(av[i],"-t")==0)
        {
            flag+=1<<FG_TIME;
        }
        else if(strcmp(av[i],"-a")==0)
        {
            flag+=(1<<FG_ALL)-1;
        }
        else if(strcmp(av[i],"-i")==0)
        {
            flag+=1<<FG_INODE;
        }
        else if(strcmp(av[i],"-m")==0)
        {
            flag+=1<<FG_MODE;
        }
        else if(strcmp(av[i],"-r")==0)
        {
            recur=1;
        }
        else if(strcmp(av[i],"-ig")==0)
        {
            ignore=FG_IGNO;
        }
        else if(strcmp(av[i],"-dl")==0)
        {
            flag_list_files=0;
        }
        else if(strcmp(av[i],"-lt")==0)
        {
            flag_list_type=1;
        }
        else if(strcmp(av[i],"-jf")==0)
        {
            just_file=1;
        }
        else if(strcmp(av[i],"-jd")==0)
        {
            just_dir=1;
        }
        else if(strcmp(av[i],"-h")==0)
        {
            hp=1;
        }
        else if(strcmp(av[i],"-p")==0)
        {
            if(i+1<ac)
            {
                pat=av[i+1];
                i+=1;
            }
            else
            {
                printf("less pattern\n");
                return -1;
            }
        }
        else
        {
            if(access(av[i],F_OK|R_OK))
            {
                perror("access");
                continue;
            }
            p=(struct path_list*)malloc(sizeof(struct path_list));
            if(!p)
            {
                perror("malloc");
                destroy_plist(pl);
                return errno;
            }
            p->path=av[i];
            p->next=pl;
            pl=p;
        }
    }

    if(flag>0)just_file=1;

    if(hp)
    {
        help();
        return 0;
    }

    if(pat)
    {
        if(regcomp(rg,pat,REG_EXTENDED|REG_ICASE)!=0)
        {
            perror("regcomp");
            return -1;
        }
    }

    if(pl==NULL)
    {
        printf("no path\n");
        return -1;
    }

    struct file_ctl*fc=NULL;
    struct file_list*fl=NULL;
    struct file_list mp;

    int done=0;

for(q=pl;q!=NULL;q=q->next)
{
    if(recur==1)
    {
        fc=recur_dir(fc,q->path,ignore);
        if(fc==NULL)
        {
            if(ignore!=0)
                continue;
            else
            {
                destroy_plist(pl);
                if(pat)
                {
                    regfree(rg);
                    pat=NULL;   
                }
                return errno;
            }
        }
        done=out_flist(fc,flag);
        destroy_fctl(fc);
        fc=NULL;
    }
    else
    {
        if(flag_list_files==1)
            printf("%s:\n",q->path);
        if(lstat(q->path,&(mp.st))!=0)
        {
            if(errno!=EOVERFLOW)
            {
                perror("stat");
                if(pat)
                {
                    regfree(rg);
                    pat=NULL;
                }
                return -1;
            }
            else
            {
                mp.err=EOVERFLOW;
                mp.size=(long long)mp.st.st_size+((long long)1<<32);
                mp.blocks=mp.size/BLOCK_SIZE;
            }
        }
        mp.path=q->path;
        mp.type=mp.st.st_mode;
        out_finf(&mp,flag);
        mp.path=NULL;
    }

}
    if(pat)
    {
        regfree(rg);
        pat=NULL;
    }

return done;
}

struct file_ctl*
recur_dir(struct file_ctl*fc,char*path,int flag)
{
    if(path==NULL || &fc==NULL)return NULL;

    fc=(struct file_ctl*)malloc(sizeof(struct file_ctl));
    if(!fc)
    {
        perror("malloc");
        return NULL;
    }
    bzero(fc,sizeof(struct file_ctl));
    fc->fl=(struct file_list*)malloc(sizeof(struct file_list));
    if(!fc->fl)
    {
        free(fc);
        perror("malloc");
        return NULL;
    }
    int plen=strlen(path);
    fc->fl->path=(char*)malloc(sizeof(char)*(plen+2));
    if(!fc->fl->path)
    {
        perror("malloc");
        free(fc->fl);
        free(fc);
        return NULL;
    }
    strncpy(fc->fl->path,path,plen);
    fc->fl->path[plen]=0;
    fc->fl->next=NULL;
    fc->count=0;
    if(lstat(path,&(fc->fl->st)))
    {
        perror("lstat");
        destroy_fctl(fc);
        return NULL;
    }
    if(S_ISDIR(fc->fl->st.st_mode))
        fc->fl->type=DT_DIR;

    strncpy(fc->fl->name,path,255);

    int ct;
    struct file_list*p=NULL,*t=NULL,*q=NULL,*buf=NULL;
    for(p=fc->fl;p!=NULL;p=p->next)
    {
        //printf("%s\n",p->path);
        if((p->st.st_mode&S_IFDIR)==S_IFDIR)
        {
            t=list_dir(p->path,&ct);
            if(t==NULL && err_empty_dir==1)
                continue;
            else
            if(t==NULL && flag==FG_IGNO)
            {
                continue;
            }
            else if(t==NULL && flag!=FG_IGNO)
            {
                printf("error:%s\n",p->path);
                destroy_fctl(fc);
                return NULL;
            }
            else if(t)
            {
                q=p->next;
                p->next=t;
                for(buf=t;buf!=NULL && buf->next!=NULL;buf=buf->next);
                buf->next=q;
            }
            fc->count+=ct;
        }
    }

return fc;
}

struct file_list*
list_dir(char*path,int*count)
{
    struct file_list*p=NULL,*q=NULL,*fl=NULL;

    int len=strlen(path);

    char* b="";

    if(path[len-1]!='/')
        b="/";
    int blen=strlen(b);

    DIR* d=opendir(path);
    if(!d)
    {
        perror("opendir");
        return NULL;
    }
    struct dirent* df=readdir(d);
    int dlen=0;
    int cc=0;
    struct stat* st=NULL;
    int err=0;
    while(df)
    {
        if(strcmp(df->d_name,"..")==0 || strcmp(df->d_name,".")==0)
            goto readd;
        if(pat)
        {
            if(df->d_type!=DT_DIR)
                err=reg_pat(df->d_name,rg);
            else err=1;
            if(err==0)
                goto readd;
            else if(err==-1)
            {
                closedir(d);
                destroy_list(fl);
                return NULL;
            }
        }

        p=(struct file_list*)malloc(sizeof(struct file_list));
        if(p==NULL)
        {
            perror("malloc");
            destroy_list(fl);
            closedir(d);
            return NULL;
        }
        p->target=NULL;
        dlen=strlen(df->d_name);
        p->path=(char*)malloc(sizeof(char)*(blen+len+dlen+2));
        if(!p->path)
        {
            free(p);
            destroy_list(fl);
            perror("malloc");
            closedir(d);
            return NULL;
        }
        strncpy(p->path,path,len);
        p->path[len]=0;
        strcat(p->path,b);
        strcat(p->path,df->d_name);
        strncpy(p->name,df->d_name,255);
        p->type=df->d_type;
        q=p;
        if(lstat(p->path,&(p->st))!=0)
        {
            p->err=errno;
            if(p->err!=EOVERFLOW)
            {
                perror("lstat");
                free(p->path);
                free(p);
                goto readd;
            }
            else
            {
                p->st.st_blksize=4096;
                p->size=((long long)1<<32)+(long long)(p->st.st_size);
                p->blocks=p->size/BLOCK_SIZE;
            }
        }
        q->next=fl;
        fl=q;
        cc++;
        readd:
        df=readdir(d);
    }
    closedir(d);
    if(count)*count=cc;
    if(cc==0)err_empty_dir=1;
return fl;
}

int out_finf(struct file_list*p, int flag)
{
    if(p)
    {
        struct stat* st=&(p->st);
        if(flag&(1<<FG_DEVID))
        {
            printf("    major:%d  minor:%d\n",major(st->st_dev),minor(st->st_dev));
        }
        if(flag&(1<<FG_INODE))
        {
            printf("    inode: %d\n",(int)st->st_ino);
        }
        if(flag&(1<<FG_MODE))
        {
            printf("    mode: %#o\n    type: ",st->st_mode&~(S_IFMT));
            /*if(p->type==DT_DIR)
                printf("directory");
            else if(p->type==DT_REG)
                printf("regular file");
            else if(p->type==DT_BLK)
                printf("block device");
            else if(p->type==DT_CHR)
                printf("character device");
            else if(p->type==DT_LNK)
                printf("link");
            else if(p->type==DT_FIFO)
                printf("fifo");
            else if(p->type==DT_SOCK)
                printf("socket");*/
            /*else */if(S_ISLNK(st->st_mode))
            {
                printf("link ; target: ");
                char buf[1024];
                int chs=readlink(p->path,buf,1023);
                if(chs>1023)chs=1023;
                buf[chs]=0;
                if(chs==-1)perror("readlink");
                else printf("%s",buf);
            }
            else if(S_ISDIR(st->st_mode))
                printf("directory");
            else if(S_ISCHR(st->st_mode))
                printf("character device");
            else if(S_ISBLK(st->st_mode))
                printf("block device");
            else if(S_ISFIFO(st->st_mode))
                printf("fifo");
            else if(S_ISREG(st->st_mode))
                printf("regular file");
            else if(S_ISSOCK(st->st_mode))
                printf("socket file");
            printf("\n");
        }
        if(flag&(1<<FG_LINKS))
        {
            printf("    links: %d\n",(int)st->st_nlink);
        }
        if(flag&(1<<FG_UID))
        {
            printf("    uid: %d\n",(int)st->st_uid);
        }
        if(flag&(1<<FG_GID))
        {
            printf("    gid: %d\n",(int)st->st_gid);
        }
        if(flag&(1<<FG_SIZE))
        {
            if(p->err!=EOVERFLOW)
            printf("    size: %dbytes, %gkb, %gmb\n",(int)st->st_size,((double)st->st_size)/1024,((double)st->st_size)/(1<<20));
            else
            printf("    size: %lldbytes, %gkb, %gmb, %ggb\n",p->size,((double)p->size)/1024,((double)p->size)/(1<<20),((double) p->size)/1024/1024/1024);
        }
        if(flag&(1<<FG_BLKS))
        {
            if(p->err!=EOVERFLOW)
            printf("    blocks: %d\n",(int)st->st_blocks);
            else
            printf("    blocks: %lld\n",p->blocks);
        }
        if(flag&(1<<FG_RDEVID))
        {
            printf("    rdevid: %d\n",(int)st->st_rdev);
        }
        if(flag&(1<<FG_BLKSZ))
        {
            printf("    block size: %dbytes\n",(int)st->st_blksize);
        }
        if(flag&(1<<FG_TIME))
        {
            printf("    time of last access: %s",ctime(&(st->st_atime)));
            printf("    time of last modification: %s",ctime(&(st->st_mtime)));
            printf("    time of last change: %s",ctime(&(st->st_ctime)));
        }
        return 0;
    }

return -1;
}

int out_flist(struct file_ctl*fc,int flag)
{
    if(!fc)return -1;

    struct file_list* p;
    double total_size=0;
    for(p=fc->fl;p!=NULL;p=p->next)
    {
        if((just_file==1 && p->type!=DT_DIR)||(just_dir==1 && p->type==DT_DIR))
        {
            if(flag_list_files==1)
                printf("%s:\n",p->path);
            else printf("-------------\n");
            printf("    name: %s\n",p->name);
            out_finf(p,flag);
        }
        total_size+=((double)p->st.st_size)/(1<<20);
    }
    if ( ! S_ISDIR(fc->fl->st.st_mode) )return 0;
    printf("total size: %gkb, %gmb;\ncounts: %d\n",total_size*1024,total_size,fc->count);

    if(flag_list_type==1)
    {
        for(p=fc->fl;p!=NULL;p=p->next)
        {
            if(p->type==DT_REG)fc->file_count++;
            else if(p->type==DT_DIR)fc->dir_count++;
            else if(p->type==DT_FIFO)fc->fifo_count++;
            else if(p->type==DT_CHR)fc->chr_count++;
            else if(p->type==DT_BLK)fc->blk_count++;
            else if(p->type==DT_LNK)fc->link_count++;
            else if(p->type==DT_SOCK)fc->sock_count++;
        }
        if(fc->dir_count>1)
            printf("directory counts: %d\n",fc->dir_count-1);
        if(fc->file_count>0)
            printf("file counts: %d\n",fc->file_count);
        if(fc->link_count>0)
            printf("link counts: %d\n",fc->link_count);
        if(fc->blk_count>0)
            printf("block counts: %d\n",fc->blk_count);
        if(fc->fifo_count>0)
            printf("fifo counts: %d\n",fc->fifo_count);
        if(fc->sock_count>0)
            printf("socket counts: %d\n",fc->sock_count);
        if(fc->chr_count>0)
            printf("character counts: %d\n",fc->chr_count);
    }

return 0;
}

void destroy_fctl(struct file_ctl*fc)
{
    if(fc)
        destroy_list(fc->fl);
    free(fc);
}

void destroy_list(struct file_list*fl)
{
    struct file_list*p;
    p=fl;
    while(p)
    {
        fl=fl->next;
        free(p->path);
        free(p);
        p=fl;
    }
}


void destroy_plist(struct path_list*pl)
{
    struct path_list*p=pl;

    while(p)
    {
        pl=pl->next;
        free(p);
        p=pl;
    }

}

void help()
{
    printf("This program list file stat.\n");
    printf("    -h:   help\n");
    printf("    -i:   list inode\n");
    printf("    -m:   list mode and type\n");
    printf("    -d:   list device ID\n");
    printf("    -b:   list the number of blocks\n");
    printf("    -bs:  list block-size\n");
    printf("    -rd:  list rdev(if it is a special file)\n");
    printf("    -s:   list the size of file\n");
    printf("    -t:   list the last time of operating file\n");
    printf("    -l:   list the number of links\n");
    printf("    -uid: list user id\n");
    printf("    -gid: list group id\n");
    printf("    -a:   list all\n");
    printf("    -jf:  just list file stat\n");
    printf("    -jd:  just list dir stat\n");
    printf("    -ig:  ignore error\n");
    printf("    -dl:  don't list path\n");
    printf("    -lt:  list the counts of each type\n");
    printf("    -r:   recursion dir\n");
    printf("    -p:   pattern in regular expression\n");
}

int reg_pat(char*str,regex_t* rg)
{
    if(!str || !rg)return -1;

    regmatch_t m[1];

    m->rm_so=-1;

    int err=regexec(rg,str,1,m,0);
    if(err==REG_NOMATCH)return 0;
    else if(err==0)return 1;
    else perror("regexec");
return -1;
}
