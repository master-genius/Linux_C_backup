#include<string.h>
#include<stdio.h>

#define fbuf(c) while((c=getchar())!='\n' && c!=' ' && c!='#')

void* fsearch(void*a,void*b,int ele_size,int n);
int main()
{
   int str1[256]={0,},str2[256]={0,};
   printf("Get two string_>");
   char c=0;
   int i=0,j=0;
   scanf("%s",str1);
       fbuf(c);
   scanf("%s",str2+j);
       fbuf(c);
   //fgets(str1,256,stdin);
   //str1[strlen(str1)-1]=0;
   //fgets(str2,256,stdin);
   //str2[strlen(str2)-1]=0;
   int* chr=(int*)fsearch(str1,str2,sizeof(int),1+j);
   if(chr!=NULL)
      printf("find:%d\n",*chr);
   else
      printf("NULL\n");
return 0;
}

void* fsearch(void* a, void* b, int ele_size, int n)
{
   void*buf;
   for(int i=0;i<n;i++)
   {
      buf=(char*)b+i*ele_size;
      if(memcmp(buf,a,ele_size)==0)
          return buf;
   }
return NULL;
}
