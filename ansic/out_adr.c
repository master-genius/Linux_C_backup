#include	<stdio.h>

int main()
{
	int adr=(1<<(sizeof(int)*8-2))+(1<<(sizeof(int)*5))+
	(1<<((sizeof(int)*3+1)))+1;
	void*v=&adr;
	char*q=(char*)v;
	int size=sizeof(adr);
	int bits=size*8;
	for(int i=bits-1,k=0;i>=0;i--)
	{
		printf("%d ",(adr&(1<<i)) >>i);
		k++;
		if(k==8)
		{
			printf("\n");
			k=0;
		}
	}
	printf("\n");

	for(int i=size-1;i>=0;i--)
	{
		printf("%p ",q+i);
		for(int j=sizeof(char)*8-1;j>=0;j--)
			printf("%d ",(*(q+i)&(1<<j)) >>j);
		printf("\n");
	}
	printf("\n");
return 0;
}
