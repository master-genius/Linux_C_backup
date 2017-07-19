#include	<stdio.h>
#include	<stdlib.h>

struct demch
{
	char dch;
	struct demch*next;
};

int out_bin(char b, int bits);

void destroy(struct demch*);

int main()
{
	struct demch* ds=NULL;
	struct demch*p=NULL;
	struct demch*q=NULL;
	//char c=0;
	ds=(struct demch*)malloc(sizeof(struct demch));
	if(ds==NULL)
	{
		perror("malloc");
		return -1;
	}
	p=q=ds;
	ds->next=NULL;
	ds->dch=0;
	while(q->dch!='\n')
	{
		p=(struct demch*)malloc(sizeof(struct demch));
		if(p==NULL)
		{
			perror("malloc");
			destroy(ds);
			return -1;
		}
		p->next=NULL;
		q->next=p;
		q=p;
		q->dch = fgetc(stdin);
	}
	int bits=sizeof(char)*8;
	for(p=ds->next;p!=NULL;p=p->next)
	{
		out_bin(p->dch,bits);
		if(p->next==NULL)
			printf("END");
		printf("\n");
	}
	destroy(ds);

return 0;
}

void destroy(struct demch* head)
{
	struct demch* p=NULL;
	p=head;
	while(p)
	{
		head=head->next;
		free(p);
		p=head;
	}
}

int out_bin(char b, int bits)
{
	if(bits <= 0 || bits > sizeof(int)*8)
		return -1;
	for(int i=bits-1;i>=0;i--)
		printf("%d",(b&(1<<i)) >> i);

return 0;
}
