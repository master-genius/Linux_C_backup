#include<stdio.h>
#include<time.h>

int main()
{
    struct tm *ptr;
    char tr[100];
    time_t tm;
    time(&tm);
    ptr=localtime(&tm);
    strftime(tr,100 ,"%I:%M:%S  %p  %A  %Y.%m.%d\n",ptr);
    printf("%s",tr);

return 0;
}
