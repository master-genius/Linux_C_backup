#include<time.h>

#define TM_PRECISION 0.000001
#define TMEND(f,u) ((float)(f)/u)
#define DEY_SEC 1000000
#define DEY_MS 1000
#define DEY_MIS 1

void delay_sec(float);
void delay_ms(float);
void delay_mis(float);

int main(int ac,char*av[])
{
     delay_sec(1);
     delay(1000);
     delay(1000000);
return 0;
}

void delay_sec(float s)
{
    if(s<=0.0)
      return ;
    clock_t start,end;
    start=clock();
    for(;;)
    {
        end=clock();
        if(TMEND(end-start,DEY_SEC)<=(s+TM_PRECISION)&&TMEND(end-start,DEY_SEC)>=(s-TM_PRECISION))
           return ;
        if(TMEND(end-start,DEY_SEC)>(s+TM_PRECISION))
          return ;
    }
}

void delay_ms(float ms)
{
    if(ms<0.0)
      return ;
    clock_t start,end;
    start=clock();
    for(;;)
    {
        end=clock();
        if(TMEND(end-start,DEY_MS)>=(ms-TM_PRECISION)&&TMEND(end-start,DEY_MS)<=(ms+TM_PRECISION))
          return ;
        if(TMEND(end-start,DEY_MS)>(ms+TM_PRECISION))
           return ;
    }
}

void delay_mis(float mis)
{
    if(mis<=0.0)
      return ;
   clock_t start,end;
   start=clock();
   for(;;)
   {
       end=clock();
       if(TMEND(end-start,DEY_MIS)<=(mis+TM_PRECISION)&&TMEND(end-start,DEY_MIS)>=(mis-TM_PRECISION))
          return ;
       if(TMEND(end-start,DEY_MIS)>(mis+TM_PRECISION))
         return ;
   }
}
