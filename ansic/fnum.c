#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MODE_CH     1
#define MODE_INT    2

struct line_char
{
    int wd;
    struct line_char* next;
};

struct lines
{
    struct line_char* head;
    struct lines* next;
};

struct lines* read_file(char*fnam);
void destroy_lines(struct lines*);

int main(int ac, char* av[])
{
    if(ac<2)
        return 0;
    struct lines* li=read_file(av[1]);
    if(!li)
        return -1;

    int mode=0;

    if(ac==3)
        if(strcmp(av[2],"-c")==0)
            mode=MODE_CH;
        else if(strcmp(av[2],"-i")==0)
            mode=MODE_INT;
        else
        {
            printf("unknow mode,using default mode\n");
            mode=MODE_CH;
        }

    struct line_char*p=NULL;
    struct lines*n=NULL;

    for(n=li;n!=NULL;n=n->next)
        for(p=n->head->next;p!=NULL;p=p->next)
        {
            if(mode==MODE_CH)
                printf("%c",(char)p->wd);
            else if(p->wd!=' ' && p->wd!='\n')
                printf("%d ",p->wd);
            else
                printf("%c",(char)p->wd);
        }
    printf("\nEND---------------------------------END\n");

    destroy_lines(li);

return 0;
}


struct lines* read_file(char*fnam)
{
    FILE* fd=fopen(fnam,"r");
    if(!fd)
    {
        perror("fopen");
        return NULL;
    }

    struct line_char* cp=NULL,*cq=NULL;
    struct lines* lp=NULL,*lq=NULL;
    struct lines*li=NULL;

    char b;

    li=(struct lines*)malloc(sizeof(struct lines));
    if(!li)
    {
        perror("malloc");
        return NULL;
    }
    li->next=NULL;
    li->head=(struct line_char*)malloc(sizeof(struct line_char));

    if(!li->head)
    {
        perror("malloc");
        free(li);
        return NULL;
    }
    li->head->next=NULL;
    lq=lp=li;
    cp=cq=li->head;

    int next_flag=0;

    while(!feof(fd))
    {
        b=fgetc(fd);
        cq=(struct line_char*)malloc(sizeof(struct line_char));
        if(!cq)
        {
            destroy_lines(li);
            perror("malloc");
            return NULL;
        }
        cp->next=cq;
        cq->next=NULL;
        cp=cq;
        cq->wd=(int)b;
        if(b=='\n')
        {
            lq=(struct lines*)malloc(sizeof(struct lines));
            if(!lq)
            {
                destroy_lines(li);
                perror("malloc");
                return NULL;
            }
            lq->next=NULL;
            lp->next=lq;
            lp=lq;
            lq->head=(struct line_char*)malloc(sizeof(struct line_char));
            if(!lq->head)
            {
                destroy_lines(li);
                perror("malloc");
                return NULL;
            }
            lq->head->next=NULL;
            cp=cq=lq->head;
        }

    }

return li;
}

void destroy_lines(struct lines*li)
{
    struct line_char* cl=NULL,*cc=NULL;
    struct lines* l=NULL;
    l=li;
    cl=cc=li->head;
    while(l)
    {
        while(cl)
        {
            cc=cc->next;
            free(cl);
            cl=cc;
        }
        li=li->next;
        free(l);
        l=li;
        if(l)
            cl=cc=l->head;
    }
}

