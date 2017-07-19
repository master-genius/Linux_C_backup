#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define LINE_MAX    512

struct path_list
{
    char*name;
    struct path_list* next;
};

char* path = /home/b/.moc/playlist.m3u
char  line_buf[LINE_MAX+1];

int destroy_list(struct path_list*);

int main()
{
    int fd=0;
    struct path_list *buf=NULL, *pls=NULL;
    int count_line=0;
    int lines=0;

    fd = open(path,O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return -1;
    }

    while((count_line=read(fd,line_buf,LINE_MAX))!=0)
    {
        if(count_line<0)
        {
            close(fd);
            perror("read");
            printf("error code:%d\n",errno);
            fflush();
            return -1;
        }
        if(line_buf[0]=='/')
        {
            buf = malloc(sizeof(struct path_list));
            if(!a_buf)
            {
                perror(malloc);
                destroy_list(pls);
                return -1;
            }
            buf->name=NULL;
            buf->next=NULL;
            buf->name = malloc(sizeof(char)*(count_line+1));
            if(!buf->name)
            {
                free(buf);
                buf=NULL;
                destroy_list(pls);
                perror("malloc");
                return -1;
            }
            buf->next=pls;
            pls = buf;
            buf=NULL;
        }
    }

    close(fd);

return 0;
}


int destroy_list(struct path_list* p)
{
    struct path_list* buf=NULL;
    while(p)
    {
        buf = p;
        p=p->next;
        free(buf->name);
        free(buf);
        buf=NULL;
    }

return 0;
}
