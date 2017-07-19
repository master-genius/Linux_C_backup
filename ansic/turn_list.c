#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct single_list
{
    char name[32];
    struct single_list* next;
};

struct single_list* build_list(char**nam, int ac);

struct single_list* turn_list(struct single_list* sl);

void destroy(struct single_list*sl);


int main(int ac, char*av[])
{
    struct single_list*li=NULL;

    li=build_list(av+1, ac-1);

    if(!li)return -1;

    printf("build list:\n");
    struct single_list*p=li;
    for(p=li;p!=NULL;p=p->next)
        printf("    %s %p--->%p\n",p->name,p,p->next);

    li=turn_list(li);
    if(!li)return -1;

    printf("after turn list:\n");

    for(p=li;p!=NULL;p=p->next)
        printf("    %s %p--->%p\n",p->name,p,p->next);

    destroy(li);
    li=NULL;

return 0;
}

struct single_list* build_list(char**nam, int ac)
{
    if(!nam || ac<=0)return NULL;

    struct single_list*sl=NULL, *p=NULL, *q=NULL;

    int i=0;
    int flag=0;
    while(i<ac)
    {
        p=(struct single_list*)malloc(sizeof(struct single_list));
        if(!p)
        {
            destroy(sl);
            perror("malloc");
            return NULL;
        }
        if(flag==0)
        {
            flag++;
            q=sl=p;
            p->next=NULL;
        }
        else
        {
            q->next=p;
            q=p;
            q->next=NULL;
        }
        strncpy(p->name,nam[i],31);

        i++;
    }


return sl;
}

struct single_list* turn_list(struct single_list* sl)
{
    if(!sl)return NULL;

    struct single_list*p=NULL, *q=NULL, *h=NULL;

    q=sl;
    h=sl->next;

    while(q)
    {
         q->next=p;
         p=q;
         q=h;
         if(h)
             h=h->next;
    }

return p;
}

void destroy(struct single_list* sl)
{
    struct single_list* p;
    p=sl;

    while(p)
    {
        sl=sl->next;
        free(p);
        p=sl;
    }

}
